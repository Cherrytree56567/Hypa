#pragma once
#include "Window.h"

namespace Hypa {
	class App {
	public:
		HYPA_API App();

		HYPA_API bool Update();

		HYPA_API std::shared_ptr<Window> GetWindow();
		HYPA_API std::shared_ptr<EventSystem> GetEventSystem();

	private:
		std::shared_ptr<Window> window;
		std::shared_ptr<EventSystem> Events;
	};
}