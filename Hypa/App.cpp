#include "App.h"

namespace Hypa {
	App::App() {
		Events = std::make_shared<EventSystem>();
		window = std::make_shared<Window>(Events);
	}

	bool App::Update() {
		window->Update();
		window->ProcessEvents();
		return !window->shouldClose();
	}

	std::shared_ptr<Window> App::GetWindow() {
		return window;
	}

	std::shared_ptr<EventSystem> App::GetEventSystem() {
		return Events;
	}
}