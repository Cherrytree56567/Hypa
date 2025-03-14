#pragma once
#include "Window.h"
#include "RenderingAPI.h"
#include "Vulkan.h"
#include "OpenGL.h"
#include "Layer.h"
#include "Rendering3D.h"

namespace Drizzle {
	class App {
	public:
		Drizzle_API App();

		Drizzle_API bool Update();

		Drizzle_API std::shared_ptr<Window> GetWindow();
		Drizzle_API std::shared_ptr<EventSystem> GetEventSystem();
		Drizzle_API std::shared_ptr<RenderingAPISystem> GetRenderingAPISystem();
		Drizzle_API std::shared_ptr<LayerDispatch> GetLayerDispatch();
		Drizzle_API std::shared_ptr<Vulkan> GetVulkan();
		Drizzle_API std::shared_ptr<OpenGL> GetOpenGL();
		Drizzle_API std::shared_ptr<Rendering3D> GetRendering3D();

	private:
		std::shared_ptr<Window> window;
		std::shared_ptr<EventSystem> Events;
		std::shared_ptr<RenderingAPISystem> rAPIsystem;
		std::shared_ptr<Vulkan> VulkanAPI;
		std::shared_ptr<OpenGL> OpenGLAPI;
		std::shared_ptr<LayerDispatch> Layerdispatch;
		std::shared_ptr<Rendering3D> Rendering3d;
	};
}