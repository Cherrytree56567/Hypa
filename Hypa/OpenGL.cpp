#include "OpenGL.h"

namespace Hypa {
	OpenGL::OpenGL(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events) {
		name = "OpenGL";
		pWindow = window;
		pEvents = Events;
	}

	void OpenGL::OnAttach() {
        HWND hwnd = glfwGetWin32Window(pWindow->GetWindow());
        HDC hdc = GetDC(hwnd);

        // Set up a pixel format descriptor
        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            24,
            8,
            0,
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        int pixelFormat = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, pixelFormat, &pfd);

        // Create a temporary context to initialize WGL extensions
        HGLRC tempContext = wglCreateContext(hdc);
        wglMakeCurrent(hdc, tempContext);

        // Load WGL extensions
        if (!gladLoadWGL(hdc)) {
            std::cerr << "Failed to initialize WGL" << std::endl;
            return -1;
        }

        // Create the real OpenGL context
        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 5,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0
        };

        HGLRC glContext = wglCreateContextAttribsARB(hdc, 0, attribs);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(tempContext);
        wglMakeCurrent(hdc, glContext);

		glfwMakeContextCurrent(pWindow->GetWindow());
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "[Hypa::Core::Window] Error: Failed to Load GL Loader." << std::endl;
			exit(-1);
		}
	}

	void OpenGL::OnDetach() {

	}

	void OpenGL::Render() {

	}

	void OpenGL::CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {

	}

	void OpenGL::RemoveShader(std::string name) {

	}

	void OpenGL::ChangeShader(std::string name) {

	}

	std::string OpenGL::GetCurrentShaderName() {
		return "";
	}

	void OpenGL::DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {

	}

	void OpenGL::AddUniform(std::string name, UniformBufferObject& ubo) {

	}
}