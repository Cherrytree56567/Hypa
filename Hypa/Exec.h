#pragma once
#include <functional>
#include <any>
#include <map>
#include <string>
#include "base.h"

namespace Hypa {
	class Exec {
	public:
		HYPA_API Exec() {}

		HYPA_API void AddFunction(std::string name, std::function<std::any(std::vector<std::any>)> func);
		HYPA_API std::any Execute(std::string name, std::vector<std::any> args);

	private:
		std::unordered_map<std::string, std::function<std::any(std::vector<std::any>)>> Functions;
	};
}