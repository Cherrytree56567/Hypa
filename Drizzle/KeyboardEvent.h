#pragma once
#include "EventSystem.h"
#include "KeyCodes.h"

namespace Drizzle {

	class KeyPressedEvent : public Event {
	public:
		Drizzle_API KeyPressedEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

		Drizzle_API KeyCode GetKeyCode() { return m_KeyCode; }

		Drizzle_API EventType GetEventType() override { return EventType::KeyPressed; }
	private:
		KeyCode m_KeyCode;
	};

	class KeyReleasedEvent : public Event {
	public:
		Drizzle_API KeyReleasedEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

		Drizzle_API KeyCode GetKeyCode() { return m_KeyCode; }

		Drizzle_API EventType GetEventType() override { return EventType::KeyReleased; }
	private:
		KeyCode m_KeyCode;
	};
}