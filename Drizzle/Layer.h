#pragma once
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "base.h"
#include "Window.h"
#include "RenderingAPI.h"

namespace Drizzle {
    class Layer {
    public:
        Drizzle_API Layer() {}

        Drizzle_API Layer(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys) : name("Layer"), pWindow(window), rAPISystem(rAPIsys) {}

        Drizzle_API virtual ~Layer() = default;
        Drizzle_API virtual void OnAttach() { }
        Drizzle_API virtual void OnDetach() { }
        Drizzle_API virtual void Render() { }

        Drizzle_API virtual bool IsShown() const { return show; }
        Drizzle_API virtual const std::string& GetName() const { return name; }
        Drizzle_API virtual void SetShow(bool value) { show = value; }
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
        std::shared_ptr<RenderingAPISystem> rAPISystem = NULL;
    };

    class LayerDispatch {
    public:
        Drizzle_API void AddLayer(std::shared_ptr<Layer> layer);
        Drizzle_API void RemoveLayerByName(const std::string& name);
        Drizzle_API void ShowHideLayerByName(const std::string& name, bool show);
        Drizzle_API std::shared_ptr<Layer> GetLayer(const std::string& name);
        Drizzle_API void PushFront(const std::string& name);
        Drizzle_API void PushForward(const std::string& name);
        Drizzle_API void PushBack(const std::string& name);
        Drizzle_API void PushBackward(const std::string& name);

        Drizzle_API void DispatchLayerRender();
        Drizzle_API void DispatchLayerDetach();
        Drizzle_API void DispatchLayerAttach();

    private:
        std::vector<std::shared_ptr<Layer>> layers;
    };
}