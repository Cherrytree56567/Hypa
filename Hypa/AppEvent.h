#pragma once
#include "EventSystem.h"

namespace Hypa {
	class WindowResizeEvent : public Event {
	public:
		HYPA_API WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		HYPA_API unsigned int GetWidth() const { return m_Width; }
		HYPA_API unsigned int GetHeight() const { return m_Height; }

		HYPA_API EventType GetEventType() override { return EventType::WindowResize; }
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowMoveEvent : public Event {
	public:
		HYPA_API WindowMoveEvent(unsigned int x, unsigned int y) : m_x(x), m_y(y) {}

		HYPA_API unsigned int GetWidth() const { return m_x; }
		HYPA_API unsigned int GetHeight() const { return m_y; }
		HYPA_API EventType GetEventType() override { return EventType::WindowMoved; }
	private:
		unsigned int m_x, m_y;
	};

	class WindowFocusEvent : public Event {
	public:
		HYPA_API WindowFocusEvent(bool isFocused) : m_is_focused(isFocused) {}

		HYPA_API bool IsFocused() const { return m_is_focused; }
		HYPA_API EventType GetEventType() override { return EventType::WindowFocus; }
	private:
		bool m_is_focused;
	};

	class WindowCloseEvent : public Event {
	public:
		HYPA_API WindowCloseEvent() = default;

		HYPA_API EventType GetEventType() override { return EventType::WindowClose; }
	};

	class AppTickEvent : public Event {
	public:
		HYPA_API AppTickEvent() = default;

		HYPA_API EventType GetEventType() override { return EventType::AppTick; }
	};

	class AppUpdateEvent : public Event {
	public:
		HYPA_API AppUpdateEvent() = default;

		HYPA_API EventType GetEventType() override { return EventType::AppUpdate; }
	};

	class AppRenderEvent : public Event {
	public:
		HYPA_API AppRenderEvent() = default;

		HYPA_API EventType GetEventType() override { return EventType::AppRender; }
	};
}