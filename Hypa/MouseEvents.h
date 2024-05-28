#pragma once
#include "EventSystem.h"
#include "MouseCodes.h"

namespace Hypa {
	class MouseMovedEvent : public Event {
	public:
		HYPA_API MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

		HYPA_API float GetX() const { return m_MouseX; }
		HYPA_API float GetY() const { return m_MouseY; }

		HYPA_API EventType GetEventType() override { return EventType::MouseMoved; }
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		HYPA_API MouseScrolledEvent(const float xOffset, const float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		HYPA_API float GetXOffset() const { return m_XOffset; }
		HYPA_API float GetYOffset() const { return m_YOffset; }

		HYPA_API EventType GetEventType() override { return EventType::MouseScrolled; }
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonPressedEvent : public Event {
	public:
		HYPA_API MouseButtonPressedEvent(const MouseCode button) : m_Button(button) {}

		HYPA_API MouseCode GetMouseButton() const { return m_Button; }

		HYPA_API EventType GetEventType() override { return EventType::MouseButtonPressed; }
	private:
		MouseCode m_Button;
	};

	class MouseButtonReleasedEvent : public Event {
	public:
		HYPA_API MouseButtonReleasedEvent(const MouseCode button) : m_Button(button) {}

		HYPA_API MouseCode GetMouseButton() const { return m_Button; }

		HYPA_API EventType GetEventType() override { return EventType::MouseButtonReleased; }
	private:
		MouseCode m_Button;
	};
}