#pragma once
#include "base.h"
#include "Layer.h"

namespace Hypa {
	class Rendering3D : public Layer {
    public:
        HYPA_API Rendering3D(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys);

        HYPA_API virtual ~Rendering3D() override;
        HYPA_API virtual void OnAttach() override { }
        HYPA_API virtual void OnDetach() override { }
        HYPA_API virtual void Render() override { }

        HYPA_API virtual bool IsShown() const override { return show; }
        HYPA_API virtual const std::string& GetName() const override { return name; }
        HYPA_API virtual void SetShow(bool value) override { show = value; }
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
        std::shared_ptr<RenderingAPISystem> rAPISystem = NULL;
	};
}