#pragma once
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "base.h"
#include "Window.h"

namespace Hypa {
    class Layer {
    public:
        HYPA_API Layer() {}

        HYPA_API Layer(std::shared_ptr<Window> window) : name("Layer"), pWindow(window) {}

        HYPA_API virtual ~Layer() = default;
        HYPA_API virtual void OnAttach() { }
        HYPA_API virtual void OnDetach() { }
        HYPA_API virtual void Render() { }

        HYPA_API virtual bool IsShown() const { return show; }
        HYPA_API virtual const std::string& GetName() const { return name; }
        HYPA_API virtual void SetShow(bool value) { show = value; }
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
    };

    class LayerDispatch {
    public:
        HYPA_API void AddLayer(std::shared_ptr<Layer> layer);
        HYPA_API void RemoveLayerByName(const std::string& name);
        HYPA_API void ShowHideLayerByName(const std::string& name, bool show);
        HYPA_API void PushFront(const std::string& name);
        HYPA_API void PushForward(const std::string& name);
        HYPA_API void PushBack(const std::string& name);
        HYPA_API void PushBackward(const std::string& name);

        HYPA_API void DispatchLayerRender();
        HYPA_API void DispatchLayerDetach();
        HYPA_API void DispatchLayerAttach();

    private:
        std::vector<std::shared_ptr<Layer>> layers;
    };
}