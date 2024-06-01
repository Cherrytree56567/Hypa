#include "RenderingAPI.h"

namespace Hypa {
    void RenderingAPISystem::AddAPI(std::shared_ptr<RenderingAPI> API) {
        renderingAPIS.push_back(API);
    }

    void RenderingAPISystem::RemoveAPIByName(const std::string& name) {
        renderingAPIS.erase(std::remove_if(renderingAPIS.begin(), renderingAPIS.end(), [&name](const auto& layer) {
            return layer->GetName() == name;
            }), renderingAPIS.end());
    }
}