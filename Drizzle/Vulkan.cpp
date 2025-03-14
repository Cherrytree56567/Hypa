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
		vkDestroyInstance(_instance, nullptr);

		destroy_swapchain();

		vkDestroyDevice(_device, nullptr);
		vkDestroySurfaceKHR(_instance, _surface, nullptr);
		vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
	}

	void Vulkan::Render() {

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