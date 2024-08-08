#pragma once
#include "base.h"
#include "Flags.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <string>

namespace Hypa {

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 color;
	};

	struct UniformBufferObject {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
		std::vector<std::pair<std::variant<int, float, double, std::string, char, char*, glm::mat2, glm::mat2x2, glm::mat2x3, glm::mat2x4, glm::mat3, glm::mat3x2, glm::mat3x3, glm::mat3x4, glm::mat4, glm::mat4x2, glm::mat4x3, glm::mat4x4, glm::vec3, glm::vec1, glm::vec2, glm::vec4>, std::string>> CustomArgs;
	};

	class RenderingAPI {
	public:
		HYPA_API RenderingAPI() {}

		HYPA_API virtual void OnAttach() { }
		HYPA_API virtual void OnDetach() { }
		HYPA_API virtual void Render() { }

		HYPA_API virtual void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {}
		HYPA_API virtual void RemoveShader(std::string name) {}
		HYPA_API virtual void ChangeShader(std::string name) {}
		HYPA_API virtual std::string GetCurrentShaderName() { return ""; }

		HYPA_API virtual void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {}

		HYPA_API virtual const std::string& GetName() const { return name; }

		HYPA_API virtual void AddUniform(std::string name, UniformBufferObject& ubo) = 0;
		HYPA_API virtual UniformBufferObject& GetUniform(std::string name) { UniformBufferObject ub; return ub; }

	private:
		Flags flags;
		std::string name;
	};

	class RenderingAPISystem {
	public:
		HYPA_API RenderingAPISystem();

		HYPA_API void AddAPI(std::shared_ptr<RenderingAPI> API);
		HYPA_API void RemoveAPIByName(const std::string& name);
		HYPA_API std::shared_ptr<RenderingAPI> GetCurrentRenderingAPI();
		HYPA_API void SwitchRenderingAPI(std::string name);
		HYPA_API std::string GetCurrentRenderingAPIName();

	private:
		std::vector<std::shared_ptr<RenderingAPI>> renderingAPIS;
		std::string CurrentRenderingAPI;
	};
}