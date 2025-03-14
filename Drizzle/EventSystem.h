#pragma once
#include <vector>
#include <memory>
#include <any>
#include <unordered_map>
#include "base.h"

namespace Drizzle {
    enum EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        ObjectMoved
    };

    class Event {
    public:
        Drizzle_API virtual ~Event() = default;

        bool Handled = false;

        Drizzle_API virtual EventType GetEventType() = 0;
    };

	class EventSystem {
	public:
        Drizzle_API EventSystem();

        typedef void (*EventCallback)(std::shared_ptr<Event> events, std::any);

        Drizzle_API void AddEvent(std::shared_ptr<Event> newEvent);
        Drizzle_API std::shared_ptr<Event> GetEvent(EventType eventType);
        Drizzle_API void RemoveHandledEvents();
        Drizzle_API bool isUnhandledEvent(EventType eventType);
        Drizzle_API void ResetEvents() { events.clear(); }
        Drizzle_API void AddEventListener(EventType eventType, EventCallback callback, std::any a = NULL);
        Drizzle_API void RemoveEventListener(EventType eventType, EventCallback callback);
        Drizzle_API void DispatchEvent();


	private:
		std::vector<std::shared_ptr<Event>> events;
        std::unordered_map<EventType, std::vector<std::pair<EventCallback, std::any>>> eventCallbacks;
	};
}