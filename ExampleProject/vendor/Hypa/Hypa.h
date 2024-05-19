#pragma once
#include <map>

#ifdef HYPA_API
#define HYPA_API __declspec(dllexport)
#else
#define HYPA_API __declspec(dllimport)
#endif // HYPA_API

HYPA_API int fnHypa();

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
	* Window
	*/

	class Window {
	public:
		HYPA_API Window();

		HYPA_API void ChangeWidth(int wid);
		HYPA_API void ChangeHeight(int wid);
		HYPA_API void ChangeTitle(char* wid);
		HYPA_API void ChangeWindowX(int wid);
		HYPA_API void ChangeWindowY(int wid);
		HYPA_API GLFWwindow* GetWindow();

	private:
		int width = 800;
		int height = 600;
		char* title = (char*)"New Hypa Game";
		int WindowX;
		int WindowY;
		GLFWwindow* window = nullptr;
		Logging log;
	};

	/*
	* Flags
	*/

	class Flags {
	public:
		HYPA_API Flags();

		HYPA_API void AddFlag(const std::string& name, bool& pointer);

		HYPA_API void ChangeFlag(const std::string& name, const bool newValue);

		HYPA_API bool GetFlag(const std::string& name);

	private:
		std::map<std::string, bool*> flagMap;
		Logging log;
	};
}