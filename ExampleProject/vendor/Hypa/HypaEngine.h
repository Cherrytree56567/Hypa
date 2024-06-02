#pragma once
#ifdef HYPA_EXPORTS
#define HYPA_API __declspec(dllexport)
#else
#define HYPA_API __declspec(dllimport)
#endif

#include <map>
#include <memory>
#include <unordered_map>
#include <string>
#include <variant>
#include <any>

typedef struct GLFWwindow GLFWwindow;

namespace Hypa {

	/*
	* Logging
	*/

	class Logging {
	public:
		HYPA_API Logging();

		HYPA_API void Error(std::string message, std::string who = "[Hypa::Core] ");
		HYPA_API void Warning(std::string message, std::string who = "[Hypa::Core] ");
		HYPA_API void Info(std::string message, std::string who = "[Hypa::Core] ");
	};

	/*
	* Flags
	*/

	class Flags {
	public:
		HYPA_API Flags();

		HYPA_API void AddFlag(const std::string& name, std::variant<int*, double*, std::string*, bool*> variable);

		HYPA_API void ChangeFlag(const std::string& name, std::variant<int, double, std::string, bool> value);

		HYPA_API std::variant<int, double, std::string, bool> GetFlag(const std::string& name);

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
		HYPA_API virtual ~Event() = default;

		bool Handled = false;

		HYPA_API virtual EventType GetEventType() = 0;
	};

	class EventSystem {
	public:
		HYPA_API EventSystem();

		typedef void (*EventCallback)(std::shared_ptr<Event> events, std::any);

		HYPA_API void AddEvent(std::shared_ptr<Event> newEvent);
		HYPA_API std::shared_ptr<Event> GetEvent(EventType eventType);
		HYPA_API void RemoveHandledEvents();
		HYPA_API bool isUnhandledEvent(EventType eventType);
		HYPA_API void ResetEvents() { events.clear(); }
		HYPA_API void AddEventListener(EventType eventType, EventCallback callback, std::any a = NULL);
		HYPA_API void RemoveEventListener(EventType eventType, EventCallback callback);
		HYPA_API void DispatchEvent();


	private:
		std::vector<std::shared_ptr<Event>> events;
		std::unordered_map<EventType, std::vector<std::pair<EventCallback, std::any>>> eventCallbacks;
	};

	/*
	* RenderingAPI
	*/
	class RenderingAPI {
	public:
		HYPA_API RenderingAPI() {}

		HYPA_API virtual void OnAttach() { }
		HYPA_API virtual void OnDetach() { }
		HYPA_API virtual void Render() { }

		HYPA_API virtual const std::string& GetName() const { return name; }

	private:
		Flags flags;
		std::string name;
	};

	class RenderingAPISystem {
	public:
		HYPA_API RenderingAPISystem() {}

		HYPA_API void AddAPI(std::shared_ptr<RenderingAPI> API);
		HYPA_API void RemoveAPIByName(const std::string& name);

	private:
		std::vector<std::shared_ptr<RenderingAPI>> renderingAPIS;
	};

	/*
	* Vulkan
	*/

	class Vulkan : public RenderingAPI {
	public:
		HYPA_API Vulkan();

		HYPA_API void OnAttach() override;
		HYPA_API void OnDetach() override;
		HYPA_API void Render() override;

		HYPA_API const std::string& GetName() const override;

	private:
		Flags flags;
		std::string name;
	};

	/*
	* Window
	*/

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

	/*
	* App
	*/

	class App {
	public:
		HYPA_API App();

		HYPA_API bool Update();

		HYPA_API std::shared_ptr<Window> GetWindow();
		HYPA_API std::shared_ptr<EventSystem> GetEventSystem();
		HYPA_API std::shared_ptr<RenderingAPISystem> GetRenderingAPISystem();

	private:
		std::shared_ptr<Window> window;
		std::shared_ptr<EventSystem> Events;
		std::shared_ptr<RenderingAPISystem> rAPIsystem;
	};
}