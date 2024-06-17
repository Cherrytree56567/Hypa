#pragma once
#include "base.h"
#include "Flags.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>

namespace Hypa {

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 color;
	};

	class IUniformBufferObject {
	public:
		virtual ~IUniformBufferObject() = default;
		virtual const glm::mat4& getModel() const = 0;
		virtual const glm::mat4& getView() const = 0;
		virtual const glm::mat4& getProj() const = 0;
		virtual void setModel(const glm::mat4& model) = 0;
		virtual void setView(const glm::mat4& view) = 0;
		virtual void setProj(const glm::mat4& proj) = 0;
	};

	template<typename... Args>
	struct UniformBufferObject : public IUniformBufferObject {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
		std::tuple<Args...> customArgs;

		const glm::mat4& getModel() const override {
			return model;
		}

		const glm::mat4& getView() const override {
			return view;
		}

		const glm::mat4& getProj() const override {
			return proj;
		}

		void setModel(const glm::mat4& newModel) override {
			model = newModel;
		}

		void setView(const glm::mat4& newView) override {
			view = newView;
		}

		void setProj(const glm::mat4& newProj) override {
			proj = newProj;
		}
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

		HYPA_API virtual void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {}

		HYPA_API virtual const std::string& GetName() const { return name; }

		HYPA_API virtual void updateUniform(const IUniformBufferObject& ubo) = 0;

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