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

	}

	void Vulkan::OnDetach() {

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