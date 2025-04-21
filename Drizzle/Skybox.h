#pragma once
#include <string>
#include "App.h"
#include "base.h"

namespace Drizzle {
	class Skybox {
	public:
		Drizzle_API Skybox(std::shared_ptr<App> app, std::string texturePath);
		Drizzle_API ~Skybox();
		Drizzle_API void LoadSkybox(std::string texturePath);
	public:
		std::string texturePath;
		std::shared_ptr<App> app;
	};
}
