#pragma once
#include "base.h"
#include "Flags.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <string>

namespace Drizzle {

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 TexCoords;
		glm::vec3 Normals;
	};

	struct UniformBufferObject {
		alignas(16) glm::mat4 model = glm::mat4(1.0f);
		alignas(16) glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		alignas(16) glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 150.0f);
		std::vector<std::pair<std::variant<int, float, double, std::string, char, char*, glm::mat2, glm::mat2x2, glm::mat2x3, glm::mat2x4, glm::mat3, glm::mat3x2, glm::mat3x3, glm::mat3x4, glm::mat4, glm::mat4x2, glm::mat4x3, glm::mat4x4, glm::vec3, glm::vec1, glm::vec2, glm::vec4>, std::string>> CustomArgs;
	};

	class RenderingAPI {
	public:
		Drizzle_API RenderingAPI() {}

		Drizzle_API virtual void OnAttach() { }
		Drizzle_API virtual void OnDetach() { }
		Drizzle_API virtual void Render() { }

		Drizzle_API virtual void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {}
		Drizzle_API virtual void RemoveShader(std::string name) {}
		Drizzle_API virtual void ChangeShader(std::string name) {}
		Drizzle_API virtual std::string GetCurrentShaderName() { return ""; }

		Drizzle_API virtual void CreateTexture(std::string name, std::string TexturePath) {}
		Drizzle_API virtual void RemoveTexture(std::string name) {}
		Drizzle_API virtual void ChangeTexture(std::string name) {}
		Drizzle_API virtual std::string GetCurrentTextureName() { return ""; }

		Drizzle_API virtual void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {}

		Drizzle_API virtual const std::string& GetName() const { return name; }

		Drizzle_API virtual void AddUniform(std::string name, UniformBufferObject& ubo) = 0;
		Drizzle_API virtual UniformBufferObject& GetUniform(std::string name) { UniformBufferObject ub; return ub; }

	private:
		Flags flags;
		std::string name;
	};

	class RenderingAPISystem {
	public:
		Drizzle_API RenderingAPISystem();

		Drizzle_API void AddAPI(std::shared_ptr<RenderingAPI> API);
		Drizzle_API void RemoveAPIByName(const std::string& name);
		Drizzle_API std::shared_ptr<RenderingAPI> GetCurrentRenderingAPI();
		Drizzle_API void SwitchRenderingAPI(std::string name);
		Drizzle_API std::string GetCurrentRenderingAPIName();

	private:
		std::vector<std::shared_ptr<RenderingAPI>> renderingAPIS;
		std::string CurrentRenderingAPI;
	};
}