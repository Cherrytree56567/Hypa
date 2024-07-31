#pragma once
#include <glad/glad.h>
#include <glad/glad_wgl.h>
#include <windows.h>
#include "RenderingAPI.h"
#include "Window.h"
#include "EventSystem.h"

namespace Hypa {
	class OpenGL : public RenderingAPI {
	public:
		HYPA_API OpenGL(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events);

		HYPA_API virtual void OnAttach() override;
		HYPA_API virtual void OnDetach() override;
		HYPA_API virtual void Render() override;

		HYPA_API virtual void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) override;
		HYPA_API virtual void RemoveShader(std::string name) override;
		HYPA_API virtual void ChangeShader(std::string name) override;
		HYPA_API virtual std::string GetCurrentShaderName() override;

		HYPA_API virtual void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) override;

		HYPA_API virtual const std::string& GetName() const override { return name; }

		HYPA_API virtual void AddUniform(std::string name, UniformBufferObject& ubo) override;

	private:
		Flags flags;
		std::string name;
		std::shared_ptr<Window> pWindow;
		std::shared_ptr<EventSystem> pEvents;
	};
}