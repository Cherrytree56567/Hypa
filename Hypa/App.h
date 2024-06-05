#pragma once
#include "Window.h"
#include "RenderingAPI.h"
#include "Vulkan.h"
#include "Layer.h"

namespace Hypa {
	class App {
	public:
		HYPA_API App();

		HYPA_API bool Update();

		HYPA_API std::shared_ptr<Window> GetWindow();
		HYPA_API std::shared_ptr<EventSystem> GetEventSystem();
		HYPA_API std::shared_ptr<RenderingAPISystem> GetRenderingAPISystem();
		HYPA_API std::shared_ptr<LayerDispatch> GetLayerDispatch();

	private:
		std::shared_ptr<Window> window;
		std::shared_ptr<EventSystem> Events;
		std::shared_ptr<RenderingAPISystem> rAPIsystem;
		std::shared_ptr<Vulkan> VulkanAPI;
		std::shared_ptr<LayerDispatch> Layerdispatch;
	};
}