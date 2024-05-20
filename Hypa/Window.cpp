#include "Window.h"

namespace Hypa {
	Window::Window() {
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
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(window);
	}
}