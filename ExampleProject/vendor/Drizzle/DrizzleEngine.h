#pragma once
#ifdef Drizzle_EXPORTS
#define Drizzle_API __declspec(dllexport)
#else
#define Drizzle_API __declspec(dllimport)
#endif

#include <map>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <variant>
#include <any>
#include <optional>
#include <array>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#define UBOVariant std::variant<int, float, double, std::string, char, char*, glm::mat2, glm::mat2x2, glm::mat2x3, glm::mat2x4, glm::mat3, glm::mat3x2, glm::mat3x3, glm::mat3x4, glm::mat4, glm::mat4x2, glm::mat4x3, glm::mat4x4, glm::vec3, glm::vec1, glm::vec2, glm::vec4>

typedef struct GLFWwindow GLFWwindow;
typedef unsigned int GLuint;

namespace Drizzle {

	/*
	* Logging
	*/

	class Logging {
	public:
		Drizzle_API Logging();

		Drizzle_API void Error(std::string message, std::string who = "[Drizzle::Core] ");
		Drizzle_API void Warning(std::string message, std::string who = "[Drizzle::Core] ");
		Drizzle_API void Info(std::string message, std::string who = "[Drizzle::Core] ");
	};

	/*
	* Flags
	*/

	class Flags {
	public:
		Drizzle_API Flags();

		Drizzle_API void AddFlag(const std::string& name, std::variant<int*, double*, std::string*, bool*> variable);

		Drizzle_API void ChangeFlag(const std::string& name, std::variant<int, double, std::string, bool> value);

		Drizzle_API std::variant<int, double, std::string, bool> GetFlag(const std::string& name);

	private:
		std::unordered_map<std::string, std::variant<int*, double*, std::string*, bool*>> flags;
		Logging log;
	};

	/*
	* Event System
	*/

    enum EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        ObjectMoved
    };

    class Event {
    public:
        Drizzle_API virtual ~Event() = default;

        bool Handled = false;

        Drizzle_API virtual EventType GetEventType() = 0;
    };

    class EventSystem {
    public:
        Drizzle_API EventSystem();

        typedef void (*EventCallback)(std::shared_ptr<Event> events, std::any);

        Drizzle_API void AddEvent(std::shared_ptr<Event> newEvent);
        Drizzle_API std::shared_ptr<Event> GetEvent(EventType eventType);
        Drizzle_API void RemoveHandledEvents();
        Drizzle_API bool isUnhandledEvent(EventType eventType);
        Drizzle_API void ResetEvents() { events.clear(); }
        Drizzle_API void AddEventListener(EventType eventType, EventCallback callback, std::any a = NULL);
        Drizzle_API void RemoveEventListener(EventType eventType, EventCallback callback);
        Drizzle_API void DispatchEvent();


    private:
        std::vector<std::shared_ptr<Event>> events;
        std::unordered_map<EventType, std::vector<std::pair<EventCallback, std::any>>> eventCallbacks;
    };

    /*
    * Events
    */

    class WindowResizeEvent : public Event {
    public:
        Drizzle_API WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

        Drizzle_API unsigned int GetWidth() const { return m_Width; }
        Drizzle_API unsigned int GetHeight() const { return m_Height; }

        Drizzle_API EventType GetEventType() override { return EventType::WindowResize; }
    private:
        unsigned int m_Width, m_Height;
    };

    class WindowMoveEvent : public Event {
    public:
        Drizzle_API WindowMoveEvent(unsigned int x, unsigned int y) : m_x(x), m_y(y) {}

        Drizzle_API unsigned int GetWidth() const { return m_x; }
        Drizzle_API unsigned int GetHeight() const { return m_y; }
        Drizzle_API EventType GetEventType() override { return EventType::WindowMoved; }
    private:
        unsigned int m_x, m_y;
    };

    class WindowFocusEvent : public Event {
    public:
        Drizzle_API WindowFocusEvent(bool isFocused) : m_is_focused(isFocused) {}

        Drizzle_API bool IsFocused() const { return m_is_focused; }
        Drizzle_API EventType GetEventType() override { return EventType::WindowFocus; }
    private:
        bool m_is_focused;
    };

    class WindowCloseEvent : public Event {
    public:
        Drizzle_API WindowCloseEvent() = default;

        Drizzle_API EventType GetEventType() override { return EventType::WindowClose; }
    };

    class AppTickEvent : public Event {
    public:
        Drizzle_API AppTickEvent() = default;

        Drizzle_API EventType GetEventType() override { return EventType::AppTick; }
    };

    class AppUpdateEvent : public Event {
    public:
        Drizzle_API AppUpdateEvent() = default;

        Drizzle_API EventType GetEventType() override { return EventType::AppUpdate; }
    };

    class AppRenderEvent : public Event {
    public:
        Drizzle_API AppRenderEvent() = default;

        Drizzle_API EventType GetEventType() override { return EventType::AppRender; }
    };

    /*
    * From GLFW.
    */
    enum KeyCode {
        Space = 32,
        Apostrophe = 39,
        Comma = 44,
        Minus = 45,
        Period = 46,
        Slash = 47,

        D0 = 48,
        D1 = 49,
        D2 = 50,
        D3 = 51,
        D4 = 52,
        D5 = 53,
        D6 = 54,
        D7 = 55,
        D8 = 56,
        D9 = 57,

        Semicolon = 59,
        Equal = 61,

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket = 91,
        Backslash = 92,
        RightBracket = 93,
        GraveAccent = 96,

        World1 = 161,
        World2 = 162,

        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348
    };

    class KeyPressedEvent : public Event {
    public:
        Drizzle_API KeyPressedEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

        Drizzle_API KeyCode GetKeyCode() { return m_KeyCode; }

        Drizzle_API EventType GetEventType() override { return EventType::KeyPressed; }
    private:
        KeyCode m_KeyCode;
    };

    class KeyReleasedEvent : public Event {
    public:
        Drizzle_API KeyReleasedEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

        Drizzle_API KeyCode GetKeyCode() { return m_KeyCode; }

        Drizzle_API EventType GetEventType() override { return EventType::KeyReleased; }
    private:
        KeyCode m_KeyCode;
    };

    enum MouseCode {
        Button1 = 0,
        Button2 = 1,
        Button3 = 2,
        Button4 = 3,
        Button5 = 4,
        Button6 = 5,
        Button7 = 6,
        Button8 = 7,

        ButtonLast = Button8,
        ButtonLeft = Button1,
        ButtonRight = Button2,
        ButtonMiddle = Button3
    };

    class MouseMovedEvent : public Event {
    public:
        Drizzle_API MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

        Drizzle_API float GetX() const { return m_MouseX; }
        Drizzle_API float GetY() const { return m_MouseY; }

        Drizzle_API EventType GetEventType() override { return EventType::MouseMoved; }
    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event {
    public:
        Drizzle_API MouseScrolledEvent(const float xOffset, const float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

        Drizzle_API float GetXOffset() const { return m_XOffset; }
        Drizzle_API float GetYOffset() const { return m_YOffset; }

        Drizzle_API EventType GetEventType() override { return EventType::MouseScrolled; }
    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonPressedEvent : public Event {
    public:
        Drizzle_API MouseButtonPressedEvent(const MouseCode button) : m_Button(button) {}

        Drizzle_API MouseCode GetMouseButton() const { return m_Button; }

        Drizzle_API EventType GetEventType() override { return EventType::MouseButtonPressed; }
    private:
        MouseCode m_Button;
    };

    class MouseButtonReleasedEvent : public Event {
    public:
        Drizzle_API MouseButtonReleasedEvent(const MouseCode button) : m_Button(button) {}

        Drizzle_API MouseCode GetMouseButton() const { return m_Button; }

        Drizzle_API EventType GetEventType() override { return EventType::MouseButtonReleased; }
    private:
        MouseCode m_Button;
    };

	/*
	* RenderingAPI
	*/

    struct Vertex {
        glm::vec3 pos;
        glm::vec3 TexCoords;
        glm::vec3 Normals;
    };

    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
        std::vector<std::pair<std::variant<int, float, double, std::string, char, char*, glm::mat2, glm::mat2x2, glm::mat2x3, glm::mat2x4, glm::mat3, glm::mat3x2, glm::mat3x3, glm::mat3x4, glm::mat4, glm::mat4x2, glm::mat4x3, glm::mat4x4, glm::vec3, glm::vec1, glm::vec2, glm::vec4>, std::string>> CustomArgs;
    };

    class RenderingAPI {
    public:
        Drizzle_API RenderingAPI() {}

        Drizzle_API virtual void OnAttach() { }
        Drizzle_API virtual void OnDetach() { }
        Drizzle_API virtual void Render() { }

        Drizzle_API virtual void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {}
        Drizzle_API virtual void RemoveShader(std::string name) {}
        Drizzle_API virtual void ChangeShader(std::string name) {}
        Drizzle_API virtual std::string GetCurrentShaderName() { return ""; }

        Drizzle_API virtual void CreateTexture(std::string name, std::string TexturePath) {}
        Drizzle_API virtual void RemoveTexture(std::string name) {}
        Drizzle_API virtual void ChangeTexture(std::string name) {}
        Drizzle_API virtual std::string GetCurrentTextureName() { return ""; }

        Drizzle_API virtual void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {}

        Drizzle_API virtual const std::string& GetName() const { return name; }

        Drizzle_API virtual void AddUniform(std::string name, UniformBufferObject& ubo) = 0;
        Drizzle_API virtual UniformBufferObject& GetUniform(std::string name) { UniformBufferObject ub; return ub; }

    private:
        Flags flags;
        std::string name;
    };

    class RenderingAPISystem {
    public:
        Drizzle_API RenderingAPISystem();

        Drizzle_API void AddAPI(std::shared_ptr<RenderingAPI> API);
        Drizzle_API void RemoveAPIByName(const std::string& name);
        Drizzle_API std::shared_ptr<RenderingAPI> GetCurrentRenderingAPI();
        Drizzle_API void SwitchRenderingAPI(std::string name);
        Drizzle_API std::string GetCurrentRenderingAPIName();

    private:
        std::vector<std::shared_ptr<RenderingAPI>> renderingAPIS;
        std::string CurrentRenderingAPI;
    };

	/*
	* Window
	*/

    class Window {
    public:
        Drizzle_API Window(std::shared_ptr<EventSystem> EvSys);

        Drizzle_API GLFWwindow* GetWindow();

        Drizzle_API void Update();
        Drizzle_API void ProcessEvents();
        Drizzle_API bool shouldClose();
        Drizzle_API std::shared_ptr<Flags> GetFlags();

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

    /*
    * Layer
    */

    class Layer {
    public:
        Drizzle_API Layer() {}

        Drizzle_API Layer(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys) : name("Layer"), pWindow(window), rAPISystem(rAPIsys) {}

        Drizzle_API virtual ~Layer() = default;
        Drizzle_API virtual void OnAttach() { }
        Drizzle_API virtual void OnDetach() { }
        Drizzle_API virtual void Render() { }

        Drizzle_API virtual void DrawObject(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {}

        Drizzle_API virtual bool IsShown() const { return show; }
        Drizzle_API virtual const std::string& GetName() const { return name; }
        Drizzle_API virtual void SetShow(bool value) { show = value; }
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
        std::shared_ptr<RenderingAPISystem> rAPISystem = NULL;
    };

    class LayerDispatch {
    public:
        Drizzle_API void AddLayer(std::shared_ptr<Layer> layer);
        Drizzle_API void RemoveLayerByName(const std::string& name);
        Drizzle_API void ShowHideLayerByName(const std::string& name, bool show);
        Drizzle_API std::shared_ptr<Layer> GetLayer(const std::string& name);
        Drizzle_API void PushFront(const std::string& name);
        Drizzle_API void PushForward(const std::string& name);
        Drizzle_API void PushBack(const std::string& name);
        Drizzle_API void PushBackward(const std::string& name);

        Drizzle_API void DispatchLayerRender();
        Drizzle_API void DispatchLayerDetach();
        Drizzle_API void DispatchLayerAttach();

    private:
        std::vector<std::shared_ptr<Layer>> layers;
    };

    /*
    * Vulkan
    */

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class Vulkan : public RenderingAPI {
    public:
        Drizzle_API Vulkan(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events);

        Drizzle_API void OnAttach() override;
        Drizzle_API void OnDetach() override;
        Drizzle_API void Render() override;

        Drizzle_API const std::string& GetName() const override;
        Drizzle_API void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) override;
        Drizzle_API void RemoveShader(std::string name) override;
        Drizzle_API void ChangeShader(std::string name) override;
        Drizzle_API std::string GetCurrentShaderName() override;

        Drizzle_API void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) override;

        Drizzle_API void AddUniform(std::string name, UniformBufferObject& ubo) override;

    private:

        Flags flags;
        std::string name;
        std::string CurrentShaderName = "Default";
        Logging log;
        bool ShaderChanged = false;
        std::shared_ptr<Window> pWindow;
        std::shared_ptr<EventSystem> pEvents;
    };

    /*
    * OpenGL
    */

    class OpenGL : public RenderingAPI {
    public:
        Drizzle_API OpenGL(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events);

        Drizzle_API virtual void OnAttach() override;
        Drizzle_API virtual void OnDetach() override;
        Drizzle_API virtual void Render() override;

        Drizzle_API virtual void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) override;
        Drizzle_API virtual void RemoveShader(std::string name) override;
        Drizzle_API virtual void ChangeShader(std::string name) override;
        Drizzle_API virtual std::string GetCurrentShaderName() override;

        Drizzle_API virtual void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) override;

        Drizzle_API virtual const std::string& GetName() const override { return name; }

        Drizzle_API virtual void AddUniform(std::string name, UniformBufferObject& ubo) override;
        Drizzle_API virtual UniformBufferObject& GetUniform(std::string name) override;

    private:
        std::tuple<unsigned int, unsigned int, UniformBufferObject> GetShader(std::string name);

        Flags flags;
        std::string name;
        std::shared_ptr<Window> pWindow;
        std::shared_ptr<EventSystem> pEvents;
        Logging log;
        std::vector<GLuint> VertexArray;
        std::vector<GLuint> VertexBuffer;
        std::vector<GLuint> IndexBuffer;
        std::vector<std::vector<uint16_t>> Indices;
        std::string CurrentShaderName = "Default";
        bool ShaderChanged = true;
        std::map<std::string, std::tuple<unsigned int, unsigned int, UniformBufferObject>> Shaders;
    };

    /*
    * Rendering3D
    */

    struct Object {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;
    };

    Drizzle_API std::pair<std::vector<Vertex>, std::vector<uint16_t>> LoadObjFile(const std::string& filePath);

    class Rendering3D : public Layer {
    public:
        Drizzle_API Rendering3D(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys);

        Drizzle_API virtual ~Rendering3D() override;
        Drizzle_API virtual void OnAttach() override;
        Drizzle_API virtual void OnDetach() override;
        Drizzle_API virtual void Render() override;

        Drizzle_API virtual bool IsShown() const override;
        Drizzle_API virtual const std::string& GetName() const override;
        Drizzle_API virtual void SetShow(bool value) override;

        Drizzle_API void CreateObject(std::string name, std::vector<Vertex> vertices, std::vector<uint16_t> indices);
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
        std::shared_ptr<RenderingAPISystem> rAPISystem = NULL;
        std::vector<std::pair<std::string, Object>> Objects;
    };

	/*
	* App
	*/

    class App {
    public:
        Drizzle_API App();

        Drizzle_API bool Update();

        Drizzle_API std::shared_ptr<Window> GetWindow();
        Drizzle_API std::shared_ptr<EventSystem> GetEventSystem();
        Drizzle_API std::shared_ptr<RenderingAPISystem> GetRenderingAPISystem();
        Drizzle_API std::shared_ptr<LayerDispatch> GetLayerDispatch();
        Drizzle_API std::shared_ptr<Vulkan> GetVulkan();
        Drizzle_API std::shared_ptr<OpenGL> GetOpenGL();
        Drizzle_API std::shared_ptr<Rendering3D> GetRendering3D();

    private:
        std::shared_ptr<Window> window;
        std::shared_ptr<EventSystem> Events;
        std::shared_ptr<RenderingAPISystem> rAPIsystem;
        std::shared_ptr<Vulkan> VulkanAPI;
        std::shared_ptr<OpenGL> OpenGLAPI;
        std::shared_ptr<LayerDispatch> Layerdispatch;
        std::shared_ptr<Rendering3D> Rendering3d;
    };
}