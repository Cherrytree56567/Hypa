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

	class Logging {
	public:
		HYPA_API Logging();

		HYPA_API void Error(std::string message, std::string who = "[Hypa::Core] ");
		HYPA_API void Warning(std::string message, std::string who = "[Hypa::Core] ");
		HYPA_API void Info(std::string message, std::string who = "[Hypa::Core] ");
	};

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

	class App {
	public:
		HYPA_API App();

		HYPA_API bool Update();

		HYPA_API std::shared_ptr<Window> GetWindow();

	private:
		std::shared_ptr<Window> window;
	};
}