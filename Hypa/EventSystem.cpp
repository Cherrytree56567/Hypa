#include "EventSystem.h"

namespace Hypa {

    EventSystem::EventSystem() {

    }

    void EventSystem::AddEvent(std::shared_ptr<Event> newEvent) {
        events.push_back(std::move(newEvent));
    }

    std::shared_ptr<Event> EventSystem::GetEvent(EventType eventType) {
        int i = 0;
        while (true) {
            if (i > events.size()) {
                break;
            }
            if (events[i]->GetEventType() == eventType && !events[i]->Handled) {
                return events[i];
            }
        }
        return nullptr;
    }

    void EventSystem::RemoveHandledEvents() {
        events.erase(
            std::remove_if(events.begin(), events.end(), [](const std::shared_ptr<Event>& event) {
                return event->Handled;
                }),
            events.end()
        );
    }

    bool EventSystem::isUnhandledEvent(EventType eventType) {
        for (auto& Eventa : events) {
            if (Eventa->GetEventType() == eventType && !Eventa->Handled) {
                return true;
            }
        }
        return false;
    }

    void EventSystem::AddEventListener(EventType eventType, EventCallback callback, std::any a) {
        eventCallbacks[eventType].push_back(std::make_pair(callback, a));
    }

    void EventSystem::RemoveEventListener(EventType eventType, EventCallback callback) {
        auto& callbacks = eventCallbacks[eventType];
        callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(),
            [callback](const std::pair<EventCallback, std::any>& listener) {
                return listener.first == callback;
            }), callbacks.end());
    }

    void EventSystem::DispatchEvent() {
        for (auto& aevent : events) {
            if (aevent == NULL) {
                // Probably give a warning that it was empty.
                continue;
            }
            if (!aevent->Handled) {
                auto& callbacks = eventCallbacks[aevent->GetEventType()];
                aevent->Handled = true;
                for (const auto& callback : callbacks) {
                    callback.first(aevent, callback.second);
                }
            }
        }
    }
}