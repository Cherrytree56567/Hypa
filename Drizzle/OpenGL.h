#pragma once
#include <glad/glad.h>
#include <windows.h>
#include "RenderingAPI.h"
#include "Window.h"
#include "EventSystem.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma comment (lib, "opengl32.lib")

namespace Drizzle {
	class OpenGL : public RenderingAPI {
	public:
		Drizzle_API OpenGL(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events);

		Drizzle_API virtual void OnAttach() override;
		Drizzle_API virtual void OnDetach() override;
		Drizzle_API virtual void Render() override;

		Drizzle_API virtual void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) override;
		Drizzle_API virtual void RemoveShader(std::string name) override;
		Drizzle_API virtual void ChangeShader(std::string name) override;
		Drizzle_API virtual std::string GetCurrentShaderName() override;

		Drizzle_API virtual void CreateTexture(std::string name, std::string TexturePath) override;
		Drizzle_API virtual void RemoveTexture(std::string name) override;
		Drizzle_API virtual void ChangeTexture(std::string name) override;
		Drizzle_API virtual std::string GetCurrentTextureName() override;

		Drizzle_API virtual void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) override;

		Drizzle_API virtual const std::string& GetName() const override { return name; }

		Drizzle_API virtual void AddUniform(std::string name, UniformBufferObject& ubo) override;
		Drizzle_API virtual UniformBufferObject& GetUniform(std::string name) override;

	private:
		std::tuple<unsigned int, unsigned int, UniformBufferObject> GetShader(std::string name);

		Flags flags;
		std::string name;
		std::shared_ptr<Window> pWindow;
		std::shared_ptr<EventSystem> pEvents;
		Logging log;
		std::vector<GLuint> VertexArray;
		std::vector<GLuint> VertexBuffer;
		std::vector<GLuint> IndexBuffer;
		std::vector<std::vector<uint16_t>> Indices;
		std::string CurrentShaderName = "Default";
		std::string CurrentTextureName = "";
		bool ShaderChanged = true;
		std::map<std::string, std::tuple<unsigned int, unsigned int, UniformBufferObject>> Shaders;
		std::map<std::string, unsigned int> Textures;
	};
}