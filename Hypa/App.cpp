#include "App.h"

namespace Hypa {
	App::App() {
		window = std::make_shared<Window>();
	}

	bool App::Update() {
		window->Update();
		window->ProcessEvents();
		return !window->shouldClose();
	}
}