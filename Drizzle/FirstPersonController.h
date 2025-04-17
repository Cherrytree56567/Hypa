#pragma once
#include <any>
#include "Camera.h"
#include "EventSystem.h"
#include "base.h"
#include "App.h"

namespace Drizzle {
	class FirstPersonController {
	public:
		Drizzle_API FirstPersonController(std::shared_ptr<App> app);

		Drizzle_API void SetSpeed(float newSpeed);
		Drizzle_API float GetSpeed() const;
		Drizzle_API void SetSensitivity(float x);
		Drizzle_API float GetSensitivity() const;
	private:
		std::shared_ptr<App> app;
		float speed = 5.0f;
		bool isMousePressed = false;
		glm::vec2 lastMousePosition;
		glm::vec2 currentMousePosition;
		glm::vec2 mouseDelta;
		float sensitivity = 0.1f;
	};
}