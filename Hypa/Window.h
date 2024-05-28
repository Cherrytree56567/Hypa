#pragma once
#include <GLFW/glfw3.h>
#include "base.h"
#include "Logging.h"
#include "Flags.h"
#include "EventSystem.h"
#include "AppEvent.h"
#include "KeyboardEvent.h"
#include "MouseEvents.h"

namespace Hypa {
	class Window {
	public:
		HYPA_API Window(std::shared_ptr<EventSystem> EvSys);

		HYPA_API GLFWwindow* GetWindow();

		HYPA_API void Update();
		HYPA_API void ProcessEvents();
		HYPA_API bool shouldClose();
		HYPA_API std::shared_ptr<Flags> GetFlags();

	private:
		int width = 800;
		int height = 600;
		std::string title = "New Hypa Game";
		int WindowX = 100;
		int WindowY = 100;
		GLFWwindow* window;
		Logging log;
		std::shared_ptr<Flags> flags = std::make_shared<Flags>();
		std::shared_ptr<EventSystem> Events = NULL;
	};
}