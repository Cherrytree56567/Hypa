#include "FirstPersonController.h"
#include "KeyboardEvent.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Drizzle {
	FirstPersonController::FirstPersonController(std::shared_ptr<App> app) : app(app) {
		app->GetEventSystem()->AddEventListener(EventType::KeyPressed, [](std::shared_ptr<Event> event, std::any a) {
			auto ts = std::any_cast<FirstPersonController*>(a);
			auto app = ts->app;
			auto keyEvent = std::dynamic_pointer_cast<KeyPressedEvent>(event);

			if (keyEvent->GetKeyCode() == A) {
				app->GetRendering3D()->GetCurrentCamera().AddMoveTo(glm::vec3(ts->GetSpeed(), 0.0f, 0.0f));
			}
			if (keyEvent->GetKeyCode() == D) {
				app->GetRendering3D()->GetCurrentCamera().AddMoveTo({ -ts->GetSpeed(), 0.0f, 0.0f });
			}
			if (keyEvent->GetKeyCode() == S) {
				app->GetRendering3D()->GetCurrentCamera().AddMoveTo({ 0.0f, 0.0f, -ts->GetSpeed() });
			}
			if (keyEvent->GetKeyCode() == W) {
				app->GetRendering3D()->GetCurrentCamera().AddMoveTo({ 0.0f, 0.0f, ts->GetSpeed() });
			}
		}, this);
	}

	void FirstPersonController::SetSpeed(float newSpeed) {
		speed = newSpeed;
	}

	float FirstPersonController::GetSpeed() const {
		return speed;
	}

	void FirstPersonController::SetSensitivity(float x) {
		sensitivity = x;
	}

	float FirstPersonController::GetSensitivity() const {
		return sensitivity;
	}
}