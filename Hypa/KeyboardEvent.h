#pragma once
#include "EventSystem.h"
#include "KeyCodes.h"

namespace Hypa {

	class KeyPressedEvent : public Event {
	public:
		HYPA_API KeyPressedEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

		HYPA_API KeyCode GetKeyCode() { return m_KeyCode; }

		HYPA_API EventType GetEventType() override { return EventType::KeyPressed; }
	private:
		KeyCode m_KeyCode;
	};

	class KeyReleasedEvent : public Event {
	public:
		HYPA_API KeyReleasedEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

		HYPA_API KeyCode GetKeyCode() { return m_KeyCode; }

		HYPA_API EventType GetEventType() override { return EventType::KeyReleased; }
	private:
		KeyCode m_KeyCode;
	};
}