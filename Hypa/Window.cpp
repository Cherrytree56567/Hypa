#include "Window.h"

namespace Hypa {
	Window::Window(std::shared_ptr<EventSystem> EvSys) : Events(EvSys) {
		flags->AddFlag("Width", &width);
		flags->AddFlag("Height", &height);
		flags->AddFlag("Title", &title);
		flags->AddFlag("WindowX", &WindowX);
		flags->AddFlag("WindowY", &WindowY);

		if (!glfwInit()) {
			log.Error("Failed to Initialize GLFW");
		}

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			log.Error("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
	}

	std::shared_ptr<Flags> Window::GetFlags() {
		return flags;
	}

	GLFWwindow* Window::GetWindow() {
		return window;
	}

	void Window::Update() {
		glfwSwapBuffers(window);
		glfwSetWindowSize(window, width, height);
		glfwSetWindowTitle(window, title.c_str());
		glfwSetWindowPos(window, WindowX, WindowY);
		std::cout << width << std::endl;
	}

	void Window::ProcessEvents() {
		glfwPollEvents();

		if (glfwWindowShouldClose(window)) {
			std::unique_ptr<WindowCloseEvent> at = std::make_unique<WindowCloseEvent>();
			Events->AddEvent(std::move(at));
		}

		if (glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE) {
			std::unique_ptr<WindowFocusEvent> at = std::make_unique<WindowFocusEvent>(true);
			Events->AddEvent(std::move(at));
		}
		else {
			std::unique_ptr<WindowFocusEvent> at = std::make_unique<WindowFocusEvent>(false);
			Events->AddEvent(std::move(at));
		}
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(window);
	}
}