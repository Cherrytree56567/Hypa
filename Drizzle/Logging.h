/*
***********************************************************************
*                                                                     *
* Drizzle3D � 2024 by Ronit D'silva is licensed under CC BY-NC-SA 4.0 *
*                                                                     *
***********************************************************************
*/
#pragma once
#include <string>
#include <iostream>
#include "base.h"

namespace Drizzle {
	class Logging {
	public:
		Drizzle_API Logging();

		Drizzle_API void Error(std::string message, std::string who = "[Drizzle::Core] ");
		Drizzle_API void Warning(std::string message, std::string who = "[Drizzle::Core] ");
		Drizzle_API void Info(std::string message, std::string who = "[Drizzle::Core] ");
	};
}