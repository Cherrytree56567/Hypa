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
	}

	void Vulkan::init_swapchain() {
		create_swapchain(std::get<int>(pWindow->GetFlags()->GetFlag("Width")), std::get<int>(pWindow->GetFlags()->GetFlag("Height")));
	}

	void Vulkan::init_commands() {

	}

	void Vulkan::init_sync_structures() {

	}
}