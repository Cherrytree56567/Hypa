#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <variant>
#include <any>
#include "base.h"
#include "Logging.h"

namespace Hypa {
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
}