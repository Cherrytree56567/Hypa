#pragma once
#include <vector>
#include <memory>
#include "base.h"

namespace Hypa {
    enum EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        ObjectMoved,
        FlagChanged
    };

    class Event {
    public:
        HYPA_API virtual ~Event() = default;

        bool Handled = false;

        HYPA_API virtual EventType GetEventType() = 0;
    };

	class EventSystem {
	public:
		EventSystem() {}

	private:
		std::vector<std::shared_ptr<Event>> events;
	};
}