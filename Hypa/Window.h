#pragma once
#include <GLFW/glfw3.h>
#include "base.h"
#include "Logging.h"
#include "Flags.h"

namespace Hypa {
	class Window {
	public:
		HYPA_API Window();

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
	};
}