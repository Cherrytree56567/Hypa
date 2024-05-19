#include "Window.h"

namespace Hypa {
	Window::Window() {
		if (!glfwInit()) {
			log.Error("Failed to Initialize GLFW");
		}

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			log.Error("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
	}

	void Window::ChangeWidth(int wid) {
		width = wid;
		glfwSetWindowSize(window, width, height);
	}

	void Window::ChangeHeight(int wid) {
		height = wid;
		glfwSetWindowSize(window, width, height);
	}

	void Window::ChangeTitle(char* wid) {
		title = wid;
		glfwSetWindowTitle(window, title);
	}

	void Window::ChangeWindowX(int wid) {
		WindowX = wid;
		glfwSetWindowPos(window, WindowX, WindowY);
	}

	void Window::ChangeWindowY(int wid) {
		WindowY = wid;
		glfwSetWindowPos(window, WindowX, WindowY);
	}

	GLFWwindow* Window::GetWindow() {
		return window;
	}

	void Window::Update() {
		glfwSwapBuffers(window);
	}

	void Window::ProcessEvents() {
		glfwPollEvents();
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(window);
	}
}