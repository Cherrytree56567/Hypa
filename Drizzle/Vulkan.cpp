#include "Vulkan.h"

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
		init_vulkan();
		init_swapchain();
		init_commands();
		init_sync_structures();
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
		}

		destroy_swapchain();

		vkDestroySurfaceKHR(_instance, _surface, nullptr);
		vkDestroyDevice(_device, nullptr);

		vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
		vkDestroyInstance(_instance, nullptr);
	}

	void Vulkan::Render() {
		/*
		* Wait until the GPU has finished rendering the last frame.
		* Timeout of 1s
		*/
		VK_CHECK(vkWaitForFences(_device, 1, &get_current_frame()._renderFence, true, 1000000000));
		VK_CHECK(vkResetFences(_device, 1, &get_current_frame()._renderFence));

		/*
		* Request image from the swapchain
		*/
		uint32_t swapchainImageIndex;
		VK_CHECK(vkAcquireNextImageKHR(_device, _swapchain, 1000000000, get_current_frame()._swapchainSemaphore, nullptr, &swapchainImageIndex));

		VkCommandBuffer command = get_current_frame()._mainCommandBuffer;

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
		VK_CHECK(vkBeginCommandBuffer(command, &cmdBeginInfo));

		/*
		* Make the swapchain image into writeable mode before rendering
		*/
		transition_image(command, _swapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);

		/*
		* Make a clear color from frame number.
		* This will flash with a 120 frame period.
		*/
		VkClearColorValue clearValue;
		float flash = std::abs(std::sin(_frameNumber / 120.f));
		clearValue = { { 0.0f, 0.0f, flash, 1.0f } };

		VkImageSubresourceRange clearRange = image_subresource_range(VK_IMAGE_ASPECT_COLOR_BIT);

		/*
		* Clear the image
		*/
		vkCmdClearColorImage(command, _swapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_GENERAL, &clearValue, 1, &clearRange);

		/*
		* Make the swapchain image into presentable mode
		*/
		transition_image(command, _swapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

		/*
		* Finalize the command buffer
		* We can no longer add commands, but it can now be executed
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

		VK_CHECK(vkQueuePresentKHR(_graphicsQueue, &presentInfo));

		/*
		* Increase the number of frames drawn
		*/
		_frameNumber++;
	}

	void Vulkan::CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {

	}

	void Vulkan::RemoveShader(std::string name) {

	}

	void Vulkan::ChangeShader(std::string name) {

	}

	std::string Vulkan::GetCurrentShaderName() {
		return CurrentShaderName;
	}

	void Vulkan::DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {

	}

	void Vulkan::AddUniform(std::string name, UniformBufferObject& ubo) {

	}
}