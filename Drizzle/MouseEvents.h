#pragma once
#include "EventSystem.h"
#include "MouseCodes.h"

namespace Drizzle {
	class MouseMovedEvent : public Event {
	public:
		Drizzle_API MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

		Drizzle_API float GetX() const { return m_MouseX; }
		Drizzle_API float GetY() const { return m_MouseY; }

		Drizzle_API EventType GetEventType() override { return EventType::MouseMoved; }
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		Drizzle_API MouseScrolledEvent(const float xOffset, const float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		Drizzle_API float GetXOffset() const { return m_XOffset; }
		Drizzle_API float GetYOffset() const { return m_YOffset; }

		Drizzle_API EventType GetEventType() override { return EventType::MouseScrolled; }
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonPressedEvent : public Event {
	public:
		Drizzle_API MouseButtonPressedEvent(const MouseCode button) : m_Button(button) {}

		Drizzle_API MouseCode GetMouseButton() const { return m_Button; }

		Drizzle_API EventType GetEventType() override { return EventType::MouseButtonPressed; }
	private:
		MouseCode m_Button;
	};

	class MouseButtonReleasedEvent : public Event {
	public:
		Drizzle_API MouseButtonReleasedEvent(const MouseCode button) : m_Button(button) {}

		Drizzle_API MouseCode GetMouseButton() const { return m_Button; }

		Drizzle_API EventType GetEventType() override { return EventType::MouseButtonReleased; }
	private:
		MouseCode m_Button;
	};
}