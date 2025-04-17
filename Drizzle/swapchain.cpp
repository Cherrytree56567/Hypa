#include "Vulkan.h"

namespace Drizzle {
	void Vulkan::create_swapchain(uint32_t width, uint32_t height) {
		vkb::SwapchainBuilder swapchainBuilder{ _chosenGPU,_device,_surface };

		_swapchainImageFormat = VK_FORMAT_B8G8R8A8_UNORM;

		vkb::SwapchainBuilder vkbSwapchainBuilder = swapchainBuilder
			//.use_default_format_selection()
			.set_desired_format(VkSurfaceFormatKHR{ .format = _swapchainImageFormat, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR });
		if (useVSync) {
			vkbSwapchainBuilder.set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR);
		} else {
			vkbSwapchainBuilder.set_desired_present_mode(VK_PRESENT_MODE_IMMEDIATE_KHR);
		}
			
		vkb::Swapchain vkbSwapchain = vkbSwapchainBuilder
			.set_desired_extent(width, height)
			.add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
			.build()
			.value();

		_swapchainExtent = vkbSwapchain.extent;
		_swapchain = vkbSwapchain.swapchain;
		_swapchainImages = vkbSwapchain.get_images().value();
		_swapchainImageViews = vkbSwapchain.get_image_views().value();

		VkFormat depthFormat = VK_FORMAT_D32_SFLOAT;

		_depthImageView = create_depth_image_view(_device, _chosenGPU, depthImageMemory, depthImage, depthFormat, width, height);

		/*
		* TODO: Change shadow quality based on flags
		* 1024 = Fast
		* 2048 = Balanced
		* 4096 = High Quality
		*/
		_shadowExtent = {
			.width = 2048,
			.height = 2048,
			.depth = 1
		};

		_shadowImage = create_image(_shadowExtent, VK_FORMAT_D32_SFLOAT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);

		VkMemoryPropertyFlags memoryFlags;

		vmaGetAllocationMemoryProperties(_allocator, _shadowImage.allocation, &memoryFlags);

		_shadowView = create_depth_image_view(_device, _chosenGPU, _shadowMemory, _shadowImage.image, VK_FORMAT_D32_SFLOAT, _shadowExtent.width, _shadowExtent.height);
	}
	
	void Vulkan::destroy_swapchain() {
		vkDestroySwapchainKHR(_device, _swapchain, nullptr);

		/*
		* Destroy swapchain resources
		*/
		for (int i = 0; i < _swapchainImageViews.size(); i++) {
			vkDestroyImageView(_device, _swapchainImageViews[i], nullptr);
		}
	}
}