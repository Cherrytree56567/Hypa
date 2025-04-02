/*
* 
* Most Code here if from the Vulkan Tutorial at https://vkguide.dev/
* 
*/
#include "Vulkan.h"

namespace Drizzle {
	void Vulkan::init_vulkan() {
		vkb::InstanceBuilder builder;

		auto inst_ret = builder.set_app_name(std::get<std::string>(pWindow->GetFlags()->GetFlag("Title")).c_str())
			.request_validation_layers(bUseValidationLayers)
			.use_default_debug_messenger()
			.require_api_version(1, 3, 0)
			.build();

		vkb::Instance vkb_inst = inst_ret.value();

		_instance = vkb_inst.instance;
		_debug_messenger = vkb_inst.debug_messenger;

		/*
		* Create Window Surface for GLFW
		*/
		if (glfwCreateWindowSurface(_instance, pWindow->GetWindow(), nullptr, &_surface) != VK_SUCCESS) {
			log.Error("Failed to create window surface!");
		}

		/*
		* Vulkan 1.3 features
		*/
		VkPhysicalDeviceVulkan13Features features{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
		features.dynamicRendering = true;
		features.synchronization2 = true;

		/*
		* Vulkan 1.2 features
		*/
		VkPhysicalDeviceVulkan12Features features12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
		features12.bufferDeviceAddress = true;
		features12.descriptorIndexing = true;

		/*
		* Use vkbootstrap to select a GPU.
		* We want a GPU that can write to the SDL surface and supports vulkan 1.3 with the correct features.
		*/
		vkb::PhysicalDeviceSelector selector{ vkb_inst };
		vkb::PhysicalDevice physicalDevice = selector
			.set_minimum_version(1, 3)
			.set_required_features_13(features)
			.set_required_features_12(features12)
			.set_surface(_surface)
			.select()
			.value();

		/*
		* Create the final Vulkan Device
		*/
		vkb::DeviceBuilder deviceBuilder{ physicalDevice };

		vkb::Device vkbDevice = deviceBuilder.build().value();

		/*
		* Get the VkDevice handle used in the rest of a Vulkan App
		*/
		_device = vkbDevice.device;
		_chosenGPU = physicalDevice.physical_device;

		/*
		* Use vkbootstrap to get a Graphics Queue
		*/
		_graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
		_graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

		/*
		* Initialize the memory allocator
		*/
		VmaAllocatorCreateInfo allocatorInfo = {};
		allocatorInfo.physicalDevice = _chosenGPU;
		allocatorInfo.device = _device;
		allocatorInfo.instance = _instance;
		allocatorInfo.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
		vmaCreateAllocator(&allocatorInfo, &_allocator);

		_mainDeletionQueue.push_function([&]() {
			vmaDestroyAllocator(_allocator);
		});
	}

	void Vulkan::init_swapchain() {
		create_swapchain(std::get<int>(pWindow->GetFlags()->GetFlag("Width")), std::get<int>(pWindow->GetFlags()->GetFlag("Height")));

		/*
		* Draw image size will match the window
		*/
		VkExtent3D drawImageExtent = {
			std::get<int>(pWindow->GetFlags()->GetFlag("Width")),
			std::get<int>(pWindow->GetFlags()->GetFlag("Height")),
			1
		};

		/*
		* Hardcoding the draw format to 32 bit float
		*/
		_drawImage.imageFormat = VK_FORMAT_R16G16B16A16_SFLOAT;
		_drawImage.imageExtent = drawImageExtent;

		VkImageUsageFlags drawImageUsages{};
		drawImageUsages |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		drawImageUsages |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		drawImageUsages |= VK_IMAGE_USAGE_STORAGE_BIT;
		drawImageUsages |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		VkImageCreateInfo rimg_info = image_create_info(_drawImage.imageFormat, drawImageUsages, drawImageExtent);

		/*
		* We want to allocate it from GPU local memory
		*/
		VmaAllocationCreateInfo rimg_allocinfo = {};
		rimg_allocinfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
		rimg_allocinfo.requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		/*
		* Allocate and create the image
		*/
		vmaCreateImage(_allocator, &rimg_info, &rimg_allocinfo, &_drawImage.image, &_drawImage.allocation, nullptr);

		/*
		* Build a image - view for the draw image to use for rendering
		*/
		VkImageViewCreateInfo rview_info = imageview_create_info(_drawImage.imageFormat, _drawImage.image, VK_IMAGE_ASPECT_COLOR_BIT);

		VK_CHECK(vkCreateImageView(_device, &rview_info, nullptr, &_drawImage.imageView));

		/*
		* Add to deletion queues
		*/
		_mainDeletionQueue.push_function([=]() {
			vkDestroyImageView(_device, _drawImage.imageView, nullptr);
			vmaDestroyImage(_allocator, _drawImage.image, _drawImage.allocation);
		});
	}

	void Vulkan::init_commands() {
		/*
		* Create a command pool for commands submitted to the graphics queue.
		* We also want the pool to allow for resetting of individual command buffers
		*/
		VkCommandPoolCreateInfo commandPoolInfo = command_pool_create_info(_graphicsQueueFamily, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

		for (int i = 0; i < FRAME_OVERLAP; i++) {

			VK_CHECK(vkCreateCommandPool(_device, &commandPoolInfo, nullptr, &_frames[i]._commandPool));

			/*
			* Allocate the default command buffer that we will use for rendering
			*/
			VkCommandBufferAllocateInfo cmdAllocInfo = command_buffer_allocate_info(_frames[i]._commandPool, 1);

			VK_CHECK(vkAllocateCommandBuffers(_device, &cmdAllocInfo, &_frames[i]._mainCommandBuffer));
		}

		VK_CHECK(vkCreateCommandPool(_device, &commandPoolInfo, nullptr, &_immCommandPool));

		/*
		* Allocate the command buffer for immediate submits
		*/
		VkCommandBufferAllocateInfo cmdAllocInfo = command_buffer_allocate_info(_immCommandPool, 1);

		VK_CHECK(vkAllocateCommandBuffers(_device, &cmdAllocInfo, &_immCommandBuffer));

		_mainDeletionQueue.push_function([=]() {
			vkDestroyCommandPool(_device, _immCommandPool, nullptr);
		});
	}

	void Vulkan::init_sync_structures() {
		/*
		* Create syncronization structures
		* - 1 fence to control when the gpu has finished rendering the frame
		* - 2 semaphores to syncronize rendering with swapchain
		* We want the fence to start signalled so we can wait on it on the first frame
		*/
		VkFenceCreateInfo fenceCreateInfo = fence_create_info(VK_FENCE_CREATE_SIGNALED_BIT);
		VkSemaphoreCreateInfo semaphoreCreateInfo = semaphore_create_info(0);

		for (int i = 0; i < FRAME_OVERLAP; i++) {
			VK_CHECK(vkCreateFence(_device, &fenceCreateInfo, nullptr, &_frames[i]._renderFence));

			VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_frames[i]._swapchainSemaphore));
			VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_frames[i]._renderSemaphore));
		}

		VK_CHECK(vkCreateFence(_device, &fenceCreateInfo, nullptr, &_immFence));
		_mainDeletionQueue.push_function([=]() { vkDestroyFence(_device, _immFence, nullptr); });
	}

	void Vulkan::init_descriptors() {
		/*
		* Create a descriptor pool that will hold 10 sets with 1 image each
		*/
		std::vector<DescriptorAllocator::PoolSizeRatio> sizes =
		{
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1 }
		};

		globalDescriptorAllocator.init_pool(_device, 10, sizes);

		/*
		* Make the descriptor set layout for our compute draw
		*/
		{
			DescriptorLayoutBuilder builder;
			builder.add_binding(0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);
			_drawImageDescriptorLayout = builder.build(_device, VK_SHADER_STAGE_COMPUTE_BIT);
		}

		/*
		* Allocate a descriptor set for our draw image
		*/
		_drawImageDescriptors = globalDescriptorAllocator.allocate(_device, _drawImageDescriptorLayout);

		VkDescriptorImageInfo imgInfo{};
		imgInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		imgInfo.imageView = _drawImage.imageView;

		VkWriteDescriptorSet drawImageWrite = {};
		drawImageWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		drawImageWrite.pNext = nullptr;

		drawImageWrite.dstBinding = 0;
		drawImageWrite.dstSet = _drawImageDescriptors;
		drawImageWrite.descriptorCount = 1;
		drawImageWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		drawImageWrite.pImageInfo = &imgInfo;

		vkUpdateDescriptorSets(_device, 1, &drawImageWrite, 0, nullptr);

		/*
		* Make sure both the descriptor allocator and the new layout get cleaned up properly
		*/
		_mainDeletionQueue.push_function([&]() {
			globalDescriptorAllocator.destroy_pool(_device);
			vkDestroyDescriptorSetLayout(_device, _drawImageDescriptorLayout, nullptr);
		});
	}

	void Vulkan::init_pipelines() {
		init_background_pipelines();
	}

	void Vulkan::init_imgui() {
		/*
		* 1: create descriptor pool for IMGUI
		*    the size of the pool is very oversize, 
		*    but it's copied from imgui demo itself.
		*/
		VkDescriptorPoolSize pool_sizes[] = { { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 } };

		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		pool_info.maxSets = 1000;
		pool_info.poolSizeCount = (uint32_t)std::size(pool_sizes);
		pool_info.pPoolSizes = pool_sizes;

		VkDescriptorPool imguiPool;
		VK_CHECK(vkCreateDescriptorPool(_device, &pool_info, nullptr, &imguiPool));

		/*
		* 2: initialize imgui library
		*/

		/*
		* This initializes the core structures of imgui
		*/
		ImGui::CreateContext();

		/*
		* This initializes imgui for SDL
		*/
		ImGui_ImplGlfw_InitForVulkan(pWindow->GetWindow(), true);

		/*
		* This initializes imgui for Vulkan
		*/
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = _instance;
		init_info.PhysicalDevice = _chosenGPU;
		init_info.Device = _device;
		init_info.Queue = _graphicsQueue;
		init_info.DescriptorPool = imguiPool;
		init_info.MinImageCount = 3;
		init_info.ImageCount = 3;
		init_info.UseDynamicRendering = true;

		/*
		* Dynamic rendering parameters for imgui to use
		*/
		init_info.PipelineRenderingCreateInfo = { .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO };
		init_info.PipelineRenderingCreateInfo.colorAttachmentCount = 1;
		init_info.PipelineRenderingCreateInfo.pColorAttachmentFormats = &_swapchainImageFormat;


		init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

		ImGui_ImplVulkan_Init(&init_info);

		ImGui_ImplVulkan_CreateFontsTexture();

		/*
		* add the destroy the imgui created structures
		*/
		_mainDeletionQueue.push_function([=]() {
			ImGui_ImplVulkan_Shutdown();
			vkDestroyDescriptorPool(_device, imguiPool, nullptr);
		});
	}

	void Vulkan::draw_background(VkCommandBuffer cmd) {
		/*
		 * Make a clear color from frame number.This will flash with a 120 frame period.
		 */
		VkClearColorValue clearValue;
		float flash = std::abs(std::sin(_frameNumber / 120.f));
		clearValue = { { 0.0f, 0.0f, flash, 1.0f } };

		VkImageSubresourceRange clearRange = image_subresource_range(VK_IMAGE_ASPECT_COLOR_BIT);

		/*
		* Bind the gradient drawing compute pipelinesss
		*/
		vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, shaders[CurrentShaderName].first);

		/*
		* Bind the descriptor set containing the draw image for the compute pipeline
		*/
		vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, shaders[CurrentShaderName].second, 0, 1, &_drawImageDescriptors, 0, nullptr);

		/*
		* Execute the push constants.
		*/
		vkCmdPushConstants(cmd, shaders[CurrentShaderName].second, VK_SHADER_STAGE_COMPUTE_BIT, 0, sizeof(PushConstants), &pushConstants);

		/*
		* Execute the compute pipeline dispatch.We are using 16x16 workgroup size so we need to divide by it
		*/
		vkCmdDispatch(cmd, std::ceil(_drawExtent.width / 16.0), std::ceil(_drawExtent.height / 16.0), 1);
	}

	void Vulkan::draw_geometry(VkCommandBuffer cmd) {
		/*
		* Begin a render pass  connected to our draw image
		*/
		VkRenderingAttachmentInfo colorAttachment = attachment_info(_drawImage.imageView, nullptr, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

		VkRenderingInfo renderInfo = rendering_info(_drawExtent, &colorAttachment, nullptr);
		vkCmdBeginRendering(cmd, &renderInfo);

		VkViewport viewport = {};
		viewport.x = 0;
		viewport.y = 0;
		viewport.width = _drawExtent.width;
		viewport.height = _drawExtent.height;
		viewport.minDepth = 0.f;
		viewport.maxDepth = 1.f;

		vkCmdSetViewport(cmd, 0, 1, &viewport);

		VkRect2D scissor = {};
		scissor.offset.x = 0;
		scissor.offset.y = 0;
		scissor.extent.width = _drawExtent.width;
		scissor.extent.height = _drawExtent.height;

		vkCmdSetScissor(cmd, 0, 1, &scissor);

		vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, shaders[CurrentShaderName].first);

		GPUDrawPushConstants push_constants;
		push_constants.worldMatrix = glm::mat4{ 1.f };

		for (size_t i = 0; i < meshes.size(); i++) {
			push_constants.vertexBuffer = meshes[i].first.vertexBufferAddress;

			vkCmdPushConstants(cmd, shaders[CurrentShaderName].second, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(GPUDrawPushConstants), &push_constants);
			vkCmdBindIndexBuffer(cmd, meshes[i].first.indexBuffer.buffer, 0, VK_INDEX_TYPE_UINT16);

			vkCmdDrawIndexed(cmd, meshes[i].second, 1, 0, 0, 0);

			
		}
		
		meshes.clear();

		vkCmdEndRendering(cmd);
	}

	void Vulkan::init_background_pipelines() {
		CreateShader("Default", "vert.spv", "frag.spv");
	}

	void Vulkan::init_default_data() {
		
	}

	void Vulkan::draw_imgui(VkCommandBuffer cmd, VkImageView targetImageView) {
		VkRenderingAttachmentInfo colorAttachment = attachment_info(targetImageView, nullptr, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
		VkRenderingInfo renderInfo = rendering_info(_swapchainExtent, &colorAttachment, nullptr);

		vkCmdBeginRendering(cmd, &renderInfo);

		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmd);

		vkCmdEndRendering(cmd);
	}

	void Vulkan::destroy_buffer(const AllocatedBuffer& buffer) {
		vmaDestroyBuffer(_allocator, buffer.buffer, buffer.allocation);
	}
}