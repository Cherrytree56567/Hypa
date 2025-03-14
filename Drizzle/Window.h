#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "base.h"
#include "Logging.h"
#include "Flags.h"
#include "EventSystem.h"
#include "AppEvent.h"
#include "KeyboardEvent.h"
#include "MouseEvents.h"

namespace Drizzle {
	class Window {
	public:
		Drizzle_API Window(std::shared_ptr<EventSystem> EvSys);

		Drizzle_API GLFWwindow* GetWindow();

		Drizzle_API void Update();
		Drizzle_API void ProcessEvents();
		Drizzle_API bool shouldClose();
		Drizzle_API std::shared_ptr<Flags> GetFlags();

		Drizzle_API void UseGLFW();
		Drizzle_API void UseNoClientApi();

	private:
		int width = 800;
		int height = 600;
		std::string title = "New Drizzle Game";
		int WindowX = 100;
		int WindowY = 100;
		GLFWwindow* window;
		Logging log;
		std::shared_ptr<Flags> flags = std::make_shared<Flags>();
		std::shared_ptr<EventSystem> Events = NULL;

		std::vector<int> key_codes;
		std::vector<int> keyRel_codes;
		bool wasLeftMouseButtonPressed = false;
		bool wasRightMouseButtonPressed = false;
		double lastMouseX = 0.0;
		double lastMouseY = 0.0;
		double lastSMouseX = 0.0;
		double lastSMouseY = 0.0;
	};
}