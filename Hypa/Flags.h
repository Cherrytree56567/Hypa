#pragma once
#include <map>
#include <string>
#include <any>
#include "base.h"
#include "Logging.h"

namespace Hypa {
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