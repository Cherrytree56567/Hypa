#pragma once
#include <GLFW/glfw3.h>
#include "base.h"
#include "Logging.h"

namespace Hypa {
	class Window {
	public:
		HYPA_API Window();

		HYPA_API void ChangeWidth(int wid);
		HYPA_API void ChangeHeight(int wid);
		HYPA_API void ChangeTitle(char* wid);
		HYPA_API void ChangeWindowX(int wid);
		HYPA_API void ChangeWindowY(int wid);
		HYPA_API GLFWwindow* GetWindow();

		HYPA_API void Update();
		HYPA_API void ProcessEvents();
		HYPA_API bool shouldClose();

	private:
		int width = 800;
		int height = 600;
		char* title = (char*)"New Hypa Game";
		int WindowX = 0;
		int WindowY = 0;
		GLFWwindow* window;
		Logging log;
	};
}