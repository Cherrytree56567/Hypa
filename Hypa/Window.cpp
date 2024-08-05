#include "Window.h"

namespace Hypa {
	double xffset, yffset = 0.0f;
	bool a = false;

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		a = true;
		xffset = xoffset;
		yffset = yoffset;
	}

	void Window::UseGLFW() {
		glfwDestroyWindow(window);
		glfwDefaultWindowHints();
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			log.Error("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		glfwGetWindowPos(window, &WindowX, &WindowY);
		glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	}

	void Window::UseNoClientApi() {
		glfwDestroyWindow(window);
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			log.Error("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		glfwGetWindowPos(window, &WindowX, &WindowY);
		glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	}

	Window::Window(std::shared_ptr<EventSystem> EvSys) : Events(EvSys) {
		flags->AddFlag("Width", &width);
		flags->AddFlag("Height", &height);
		flags->AddFlag("Title", &title);
		flags->AddFlag("WindowX", &WindowX);
		flags->AddFlag("WindowY", &WindowY);

		if (!glfwInit()) {
			log.Error("Failed to Initialize GLFW");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			log.Error("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		glfwGetWindowPos(window, &WindowX, &WindowY);
		glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
		key_codes.clear();
		keyRel_codes.clear();
	}

	void Window::ProcessEvents() {
		glfwPollEvents();

		int newWidth, newHeight;
		glfwGetFramebufferSize(window, &newWidth, &newHeight);

		if (newWidth != width || newHeight != height) {
			width = newWidth;
			height = newHeight;
			Events->AddEvent(std::make_shared<WindowResizeEvent>((unsigned int)width, (unsigned int)height));
		}

		if (glfwWindowShouldClose(window)) {
			Events->AddEvent(std::make_shared<WindowCloseEvent>());
		}

		if (glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE) {
			Events->AddEvent(std::make_shared<WindowFocusEvent>(true));
		}
		else {
			Events->AddEvent(std::make_shared<WindowFocusEvent>(false));
		}

		int x, y;
		glfwGetWindowPos(window, &x, &y);
		if (x != WindowX) {
			WindowX = x;
			WindowY = y;
			Events->AddEvent(std::make_shared<WindowMoveEvent>((unsigned int)WindowX, (unsigned int)WindowY));
		}
		else if (y != WindowY) {
			WindowX = x;
			WindowY = y;
			Events->AddEvent(std::make_shared<WindowMoveEvent>((unsigned int)WindowX, (unsigned int)WindowY));
		}

		for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				Events->AddEvent(std::make_shared<KeyPressedEvent>((KeyCode)key));
			}
			if (glfwGetKey(window, key) == GLFW_RELEASE) {
				Events->AddEvent(std::make_shared<KeyReleasedEvent>((KeyCode)key));
			}
		}

		int blef = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		int bmid = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
		int brig = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		int blas = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LAST);
		int beig = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_8);
		int bsev = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_7);
		int bsix = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_6);
		int bfiv = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_5);
		int bfor = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_4);
		int btre = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3);
		int btwo = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);
		int bone = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);

		if (blef == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>(((MouseCode)blef)));
		}
		else if (blef == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)blef));
		}

		if (bmid == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)bmid));
		}
		else if (bmid == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)bmid));
		}

		if (brig == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)brig));
		}
		else if (brig == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)brig));
		}

		if (blas == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)blas));
		}
		else if (blas == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)blas));
		}

		if (beig == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)beig));
		}
		else if (beig == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)beig));
		}

		if (bsev == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)bsev));
		}
		else if (bsev == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)bsev));
		}

		if (bsix == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)bsix));
		}
		else if (bsix == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)bsix));
		}

		if (bfiv == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)bfiv));
		}
		else if (bfiv == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)bfiv));
		}

		if (bfor == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)bfor));
		}
		else if (bfor == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)bfor));
		}

		if (btre == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)btre));
		}
		else if (btre == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)btre));
		}

		if (btwo == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)btwo));
		}
		else if (btwo == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)btwo));
		}

		if (bone == GLFW_PRESS) {
			Events->AddEvent(std::make_shared<MouseButtonPressedEvent>((MouseCode)bone));
		}
		else if (bone == GLFW_RELEASE) {
			Events->AddEvent(std::make_shared<MouseButtonReleasedEvent>((MouseCode)bone));
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		if (mouseX != lastMouseX || mouseY != lastMouseY) {
			lastMouseX = mouseX;
			lastMouseY = mouseY;
			Events->AddEvent(std::make_shared<MouseMovedEvent>((float)lastMouseX, (float)lastMouseY));
		}

		if (a == true) {
			a = false;
			Events->AddEvent(std::make_shared<MouseScrolledEvent>((float)xffset, (float)yffset));
		}
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(window);
	}
}