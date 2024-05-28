#pragma once
#include <vector>
#include <memory>
#include <any>
#include <unordered_map>
#include "base.h"

namespace Hypa {
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
        HYPA_API virtual ~Event() = default;

        bool Handled = false;

        HYPA_API virtual EventType GetEventType() = 0;
    };

	class EventSystem {
	public:
        HYPA_API EventSystem();

        typedef void (*EventCallback)(std::shared_ptr<Event> events, std::any);

        HYPA_API void AddEvent(std::shared_ptr<Event> newEvent);
        HYPA_API std::shared_ptr<Event> GetEvent(EventType eventType);
        HYPA_API void RemoveHandledEvents();
        HYPA_API bool isUnhandledEvent(EventType eventType);
        HYPA_API void ResetEvents() { events.clear(); }
        HYPA_API void AddEventListener(EventType eventType, EventCallback callback, std::any a = NULL);
        HYPA_API void RemoveEventListener(EventType eventType, EventCallback callback);
        HYPA_API void DispatchEvent();


	private:
		std::vector<std::shared_ptr<Event>> events;
        std::unordered_map<EventType, std::vector<std::pair<EventCallback, std::any>>> eventCallbacks;
	};
}