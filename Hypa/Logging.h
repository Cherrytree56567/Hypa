/*
***********************************************************************
*                                                                     *
* Drizzle3D © 2024 by Ronit D'silva is licensed under CC BY-NC-SA 4.0 *
*                                                                     *
***********************************************************************
*/
#pragma once
#include <string>
#include <iostream>
#include "base.h"

namespace Hypa {
	class Logging {
	public:
		HYPA_API Logging();

		HYPA_API void Error(std::string message, std::string who = "[Hypa::Core] ");
		HYPA_API void Warning(std::string message, std::string who = "[Hypa::Core] ");
		HYPA_API void Info(std::string message, std::string who = "[Hypa::Core] ");
	};
}