#include "RenderingAPI.h"

namespace Hypa {
    RenderingAPISystem::RenderingAPISystem() {
        CurrentRenderingAPI = "NONE";
    }

    void RenderingAPISystem::AddAPI(std::shared_ptr<RenderingAPI> API) {
        renderingAPIS.push_back(API);
    }

    void RenderingAPISystem::RemoveAPIByName(const std::string& name) {
        renderingAPIS.erase(std::remove_if(renderingAPIS.begin(), renderingAPIS.end(), [&name](const auto& layer) {
            return layer->GetName() == name;
            }), renderingAPIS.end());
    }

    std::shared_ptr<RenderingAPI> RenderingAPISystem::GetCurrentRenderingAPI() {
        for (const auto& api : renderingAPIS) {
            if (api->GetName() == CurrentRenderingAPI) {
                return api;
            }
        }
        return nullptr;
    }

    void RenderingAPISystem::SwitchRenderingAPI(std::string name) {
        for (const auto& api : renderingAPIS) {
            if (api->GetName() == name) {
                if (CurrentRenderingAPI != "NONE") {
                    GetCurrentRenderingAPI()->OnDetach();
                }
                CurrentRenderingAPI = name;
                GetCurrentRenderingAPI()->OnAttach();
            }
        }
    }

    std::string RenderingAPISystem::GetCurrentRenderingAPIName() {
        return CurrentRenderingAPI;
    }
}