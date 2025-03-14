#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <variant>
#include <any>
#include "base.h"
#include "Logging.h"

namespace Drizzle {
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
}