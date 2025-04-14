#include "Vulkan.h"
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Drizzle {
	Vulkan::Vulkan(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events) {
		name = "Vulkan";
        pWindow = window;
        pEvents = Events;
	}

	const std::string& Vulkan::GetName() const {
		return name;
	}

	void Vulkan::OnAttach() {
		flags.AddFlag("UseDedicatedGPU", &useDedicated);
		flags.AddFlag("UseVSync", &useVSync);
		flags.ChangeFlag("UseDedicatedGPU", true);
		init_vulkan();
		init_swapchain();
		init_commands();
		init_sync_structures();
		init_descriptors();
		init_pipelines();
		init_imgui();
		init_default_data();
	}

	void Vulkan::OnDetach() {
		/*
		* Make sure the GPU has stopped doing its things
		*/
		vkDeviceWaitIdle(_device);

		for (int i = 0; i < FRAME_OVERLAP; i++) {
			vkDestroyCommandPool(_device, _frames[i]._commandPool, nullptr);

			/*
			* Destroy sync objects
			*/
			vkDestroyFence(_device, _frames[i]._renderFence, nullptr);
			vkDestroySemaphore(_device, _frames[i]._renderSemaphore, nullptr);
			vkDestroySemaphore(_device, _frames[i]._swapchainSemaphore, nullptr);

			_frames[i]._deletionQueue.flush();
		}

		for (auto mesh : meshes) {
			destroy_buffer(mesh.second.indexBuffer);
			destroy_buffer(mesh.second.vertexBuffer);
		}

		if (_depthImageView != VK_NULL_HANDLE) {
			vkDestroyImageView(_device, _depthImageView, nullptr);
			_depthImageView = VK_NULL_HANDLE;
		}

		if (depthImageMemory != VK_NULL_HANDLE) {
			vkFreeMemory(_device, depthImageMemory, nullptr);
			depthImageMemory = VK_NULL_HANDLE;
		}

		if (depthImage != VK_NULL_HANDLE) {
			vkDestroyImage(_device, depthImage, nullptr);
			depthImage = VK_NULL_HANDLE;
		}

		_texDeletionQueue.flush();
		_mainDeletionQueue.flush();

		destroy_swapchain();

		vkDestroySurfaceKHR(_instance, _surface, nullptr);
		vkDestroyDevice(_device, nullptr);

		vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
		vkDestroyInstance(_instance, nullptr);
	}

	void Vulkan::RenderBefore() {
		_drawExtent.height = std::min(_swapchainExtent.height, _drawImage.imageExtent.height) * renderScale;
		_drawExtent.width = std::min(_swapchainExtent.width, _drawImage.imageExtent.width) * renderScale;
		if (resize_requested) {
			resize_swapchain();
		}
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Begin("background")) {

			ImGui::Checkbox("Use VSync", &useVSync);

			ImGui::Text("Selected shader: ", CurrentShaderName);

			ImGui::SliderFloat("Render Scale", &renderScale, 0.3f, 1.f);
			ImGui::InputFloat4("data1", (float*)&pushConstants.worldMatrix[0]);
			ImGui::InputFloat4("data2", (float*)&pushConstants.worldMatrix[1]);
			ImGui::InputFloat4("data3", (float*)&pushConstants.worldMatrix[2]);
			ImGui::InputFloat4("data4", (float*)&pushConstants.worldMatrix[3]);

			float fps = 1000.0f / engineStats.frametime;
			ImGui::Text("frametime %f ms", engineStats.frametime);
			ImGui::Text("fps %f", fps);
			ImGui::Text("draw time %f ms", engineStats.mesh_draw_time);
			ImGui::Text("update time %f ms", engineStats.scene_update_time);
			ImGui::Text("triangles %i", engineStats.triangle_count);
			ImGui::Text("draws %i", engineStats.drawcall_count);
		}
		ImGui::End();

		ImGui::Render();
		/*
		* Wait until the GPU has finished rendering the last frame.
		* Timeout of 1s
		*/
		VK_CHECK(vkWaitForFences(_device, 1, &get_current_frame()._renderFence, true, 1000000000));

		get_current_frame()._deletionQueue.flush();
		get_current_frame()._frameDescriptors.clear_pools(_device);
		VK_CHECK(vkResetFences(_device, 1, &get_current_frame()._renderFence));

		/*
		* Request image from the swapchain
		*/
		VkResult e = vkAcquireNextImageKHR(_device, _swapchain, 1000000000, get_current_frame()._swapchainSemaphore, nullptr, &swapchainImageIndex);
		if (e == VK_ERROR_OUT_OF_DATE_KHR) {
			resize_requested = true;
			return;
		}

		get_current_frame()._deletionQueue.flush();

		command = get_current_frame()._mainCommandBuffer;

		/*
		* Now that we are sure that the commands finished executing,
		* we can safely reset the command buffer to begin recording again.
		*/
		VK_CHECK(vkResetCommandBuffer(command, 0));

		/*
		* Begin the command buffer recording.
		* We will use this command buffer exactly once,
		* so we want to let Vulkan know that.
		*/
		VkCommandBufferBeginInfo cmdBeginInfo = command_buffer_begin_info(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

		/*
		* Start the command buffer recording
		*/
		_drawExtent.width = _drawImage.imageExtent.width;
		_drawExtent.height = _drawImage.imageExtent.height;

		VK_CHECK(vkBeginCommandBuffer(command, &cmdBeginInfo));

		/*
		* Transition our main draw image into general layout so we can write into it
		* We will overwrite it all so we dont care about what was the older layout
		*/
		transition_image(command, _drawImage.image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);

		transition_image(command, _drawImage.image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

		renderBefore = true;

		engineStats.drawcall_count = 0;
		engineStats.triangle_count = 0;

		start = std::chrono::system_clock::now();
	}

	void Vulkan::RenderAfter() {
		if (renderBefore == false) {
			log.Error("RenderBefore was not called before RenderAfter");
			return;
		} else {
			renderBefore = false;
		}

		auto end = std::chrono::system_clock::now();

		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		engineStats.mesh_draw_time = elapsed.count() / 1000.f;
		/*
		* Transtion the draw image and the swapchain image into their correct transfer layouts
		*/
		transition_image(command, _drawImage.image, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
		transition_image(command, _swapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		/*
		* Execute a copy from the draw image into the swapchain
		*/
		copy_image_to_image(command, _drawImage.image, _swapchainImages[swapchainImageIndex], _drawExtent, _swapchainExtent);

		/*
		* Set swapchain image layout to Attachment Optimal so we can draw it
		*/
		transition_image(command, _swapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

		/*
		* Draw imgui into the swapchain image
		*/
		draw_imgui(command, _swapchainImageViews[swapchainImageIndex]);

		/*
		* Set swapchain image layout to Present so we can show it on the screen
		*/
		transition_image(command, _swapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

		/*
		* Finalize the command buffer
		*/
		VK_CHECK(vkEndCommandBuffer(command));

		/*
		* Prepare the submission to the queue.
		* We want to wait on the _presentSemaphore, as that semaphore is signaled when the swapchain is ready
		* We will signal the _renderSemaphore, to signal that rendering has finished
		*/
		VkCommandBufferSubmitInfo cmdinfo = command_buffer_submit_info(command);

		VkSemaphoreSubmitInfo waitInfo = semaphore_submit_info(VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR, get_current_frame()._swapchainSemaphore);
		VkSemaphoreSubmitInfo signalInfo = semaphore_submit_info(VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT, get_current_frame()._renderSemaphore);

		VkSubmitInfo2 submit = submit_info(&cmdinfo, &signalInfo, &waitInfo);

		/*
		* Submit command buffer to the queue and execute it.
		* _renderFence will now block until the graphic commands finish execution
		*/
		VK_CHECK(vkQueueSubmit2(_graphicsQueue, 1, &submit, get_current_frame()._renderFence));

		/*
		* Prepare Present
		* This will put the image we just rendered to into the visible window.
		* We want to wait on the _renderSemaphore for that, 
		* as its necessary that drawing commands have finished before the image is displayed to the user
		*/
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.pNext = nullptr;
		presentInfo.pSwapchains = &_swapchain;
		presentInfo.swapchainCount = 1;

		presentInfo.pWaitSemaphores = &get_current_frame()._renderSemaphore;
		presentInfo.waitSemaphoreCount = 1;

		presentInfo.pImageIndices = &swapchainImageIndex;

		VkResult presentResult = vkQueuePresentKHR(_graphicsQueue, &presentInfo);
		if (presentResult == VK_ERROR_OUT_OF_DATE_KHR) {
			resize_requested = true;
		}

		/*
		* Increase the number of frames drawn
		*/
		_frameNumber++;
	}

	void Vulkan::Render3D(std::vector<APIObject> objs, std::vector<Lighting> lights) {
		if (renderBefore == false) {
			log.Error("RenderBefore was not called before Render3D");
			return;
		}
		draw_geometry(command, objs, lights);
	}

	void Vulkan::CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {
		VkPipeline pipeline;
		VkPipelineLayout pipelineLayout;
		VkShaderModule FragShader;
		if (!load_shader_module(FragShaderPath.c_str(), _device, &FragShader)) {
			log.Error("Couldn't Build the fragment shader module.");
		} else {
			log.Info("Fragment shader succesfully loaded.");
		}

		VkShaderModule VertexShader;
		if (!load_shader_module(VertShaderPath.c_str(), _device, &VertexShader)) {
			log.Error("Couldn't build the vertex shader module");
		}
		else {
			log.Info("Vertex shader succesfully loaded.");
		}

		/*
		* Build the pipeline layout that controls the inputs / outputs of the shader
		* We are not using descriptor sets or other systems yet, so no need to use anything other than empty default
		*/
		VkPushConstantRange bufferRange{};
		bufferRange.offset = 0;
		bufferRange.size = sizeof(GPUDrawPushConstants);
		bufferRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayout setLayouts[] = {
			_singleImageDescriptorLayout
		};

		VkPipelineLayoutCreateInfo pipeline_layout_info = pipeline_layout_create_info();
		pipeline_layout_info.pPushConstantRanges = &bufferRange;
		pipeline_layout_info.pushConstantRangeCount = 1;
		pipeline_layout_info.pSetLayouts = setLayouts;
		pipeline_layout_info.setLayoutCount = 1;
		VK_CHECK(vkCreatePipelineLayout(_device, &pipeline_layout_info, nullptr, &pipelineLayout));

		PipelineBuilder pipelineBuilder;

		pipelineBuilder._pipelineLayout = pipelineLayout;
		pipelineBuilder.set_shaders(VertexShader, FragShader);
		pipelineBuilder.set_input_topology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
		pipelineBuilder.set_polygon_mode(VK_POLYGON_MODE_FILL);
		pipelineBuilder.set_cull_mode(VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_COUNTER_CLOCKWISE);
		pipelineBuilder.set_multisampling_none();
		pipelineBuilder.disable_blending();
		pipelineBuilder.enable_depthtest(true, VK_COMPARE_OP_LESS);

		pipelineBuilder.set_color_attachment_format(_drawImage.imageFormat);
		pipelineBuilder.set_depth_format(VK_FORMAT_D32_SFLOAT);

		pipeline = pipelineBuilder.build_pipeline(_device);

		vkDestroyShaderModule(_device, FragShader, nullptr);
		vkDestroyShaderModule(_device, VertexShader, nullptr);

		shaders.insert(std::make_pair(name, std::make_pair(pipeline, pipelineLayout)));

		_mainDeletionQueue.push_function([name, this]() {
			vkDestroyPipelineLayout(_device, shaders[name].second, nullptr);
			vkDestroyPipeline(_device, shaders[name].first, nullptr);
		});
	}

	void Vulkan::RemoveShader(std::string name) {
		vkDestroyPipelineLayout(_device, shaders[name].second, nullptr);
		vkDestroyPipeline(_device, shaders[name].first, nullptr);
		shaders.erase(name);
	}

	void Vulkan::ChangeShader(std::string name) {
		CurrentShaderName = name;
	}

	std::string Vulkan::GetCurrentShaderName() {
		return CurrentShaderName;
	}

	void Vulkan::AddObject(APIObject obj) {
		GPUMeshBuffers main = uploadMesh(obj.indices, obj.vertices);
		meshes[obj.name] = main;
	}

	void Vulkan::RemoveObject(std::string name) {
		if (meshes.contains(name)) {
			destroy_buffer(meshes[name].vertexBuffer);
			destroy_buffer(meshes[name].indexBuffer);
			meshes.erase(name);
			return;
		}
	}

	void Vulkan::CreateTexture(std::string name, std::string TexturePath) {
		AllocatedImage tex;
		int width, height, channels;
		unsigned char* data = stbi_load(TexturePath.c_str(), &width, &height, &channels, 0);
		if (!data) {
			tex = _errorCheckerboardImage;
			log.Error("Couldn't load texture: " + TexturePath);
		} else {
			if (channels == 4) {
				tex = create_image(data, VkExtent3D{ (unsigned int)width, (unsigned int)height, 1 }, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_SAMPLED_BIT);
			} else if (channels == 3) {
				tex = create_image(data, VkExtent3D{ (unsigned int)width, (unsigned int)height, 1 }, VK_FORMAT_R8G8B8_UNORM, VK_IMAGE_USAGE_SAMPLED_BIT);
			}

			_texDeletionQueue.push_function([&, name]() {
				if (textures.count(name) > 0) {
					destroy_image(textures[name]);
				}
			});
		}

		stbi_image_free(data);

		textures[name] = tex;
	}

	void Vulkan::RemoveTexture(std::string name) {
		destroy_image(textures[name]);
		textures.erase(name);
	}

	bool Vulkan::TextureExists(std::string name) {
		return textures.find(name) != textures.end();
	}
}