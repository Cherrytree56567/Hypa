#pragma once
#include "EventSystem.h"

namespace Drizzle {
	class WindowResizeEvent : public Event {
	public:
		Drizzle_API WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		Drizzle_API unsigned int GetWidth() const { return m_Width; }
		Drizzle_API unsigned int GetHeight() const { return m_Height; }

		Drizzle_API EventType GetEventType() override { return EventType::WindowResize; }
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowMoveEvent : public Event {
	public:
		Drizzle_API WindowMoveEvent(unsigned int x, unsigned int y) : m_x(x), m_y(y) {}

		Drizzle_API unsigned int GetWidth() const { return m_x; }
		Drizzle_API unsigned int GetHeight() const { return m_y; }
		Drizzle_API EventType GetEventType() override { return EventType::WindowMoved; }
	private:
		unsigned int m_x, m_y;
	};

	class WindowFocusEvent : public Event {
	public:
		Drizzle_API WindowFocusEvent(bool isFocused) : m_is_focused(isFocused) {}

		Drizzle_API bool IsFocused() const { return m_is_focused; }
		Drizzle_API EventType GetEventType() override { return EventType::WindowFocus; }
	private:
		bool m_is_focused;
	};

	class WindowCloseEvent : public Event {
	public:
		Drizzle_API WindowCloseEvent() = default;

		Drizzle_API EventType GetEventType() override { return EventType::WindowClose; }
	};

	class AppTickEvent : public Event {
	public:
		Drizzle_API AppTickEvent() = default;

		Drizzle_API EventType GetEventType() override { return EventType::AppTick; }
	};

	class AppUpdateEvent : public Event {
	public:
		Drizzle_API AppUpdateEvent() = default;

		Drizzle_API EventType GetEventType() override { return EventType::AppUpdate; }
	};

	class AppRenderEvent : public Event {
	public:
		Drizzle_API AppRenderEvent() = default;

		Drizzle_API EventType GetEventType() override { return EventType::AppRender; }
	};
}