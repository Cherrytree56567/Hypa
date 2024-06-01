#include "App.h"

namespace Hypa {
	App::App() {
		Events = std::make_shared<EventSystem>();
		window = std::make_shared<Window>(Events);
		rAPIsystem = std::make_shared<RenderingAPISystem>();
	}

	bool App::Update() {
		Events->ResetEvents();
		window->Update();
		Events->AddEvent(std::make_shared<AppTickEvent>());
		Events->AddEvent(std::make_shared<AppUpdateEvent>());
		Events->DispatchEvent();
		window->ProcessEvents();
		Events->AddEvent(std::make_shared<AppRenderEvent>());
		return !window->shouldClose();
	}

	std::shared_ptr<Window> App::GetWindow() {
		return window;
	}

	std::shared_ptr<EventSystem> App::GetEventSystem() {
		return Events;
	}

	std::shared_ptr<RenderingAPISystem> App::GetRenderingAPISystem() {
		return rAPIsystem;
	}
}