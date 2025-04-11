#pragma once
#include "base.h"
#include "Flags.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <string>

namespace Drizzle {

	struct Vertex {
		glm::vec3 position;
		float uv_x;
		glm::vec3 normal;
		float uv_y;
		glm::vec4 color;
	};

	struct PushConstants {
		glm::mat4 worldMatrix;
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

		Drizzle_API virtual PushConstants& GetPushConstants() { return pushConstants; }

	private:
		Flags flags;
		std::string name;
		PushConstants pushConstants;
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