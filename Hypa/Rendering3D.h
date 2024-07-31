#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "base.h"
#include "Layer.h"

namespace Hypa {

    HYPA_API std::pair<std::vector<float>, std::vector<unsigned int>> LoadObjFile(const std::string& filePath);

	class Rendering3D : public Layer {
    public:
        HYPA_API Rendering3D(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys);

        HYPA_API virtual ~Rendering3D() override;
        HYPA_API virtual void OnAttach() override;
        HYPA_API virtual void OnDetach() override;
        HYPA_API virtual void Render() override;

        HYPA_API virtual bool IsShown() const override;
        HYPA_API virtual const std::string& GetName() const override;
        HYPA_API virtual void SetShow(bool value) override;

        HYPA_API virtual void DrawObject(std::vector<Vertex> vertices, std::vector<uint16_t> indices) override;
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
        std::shared_ptr<RenderingAPISystem> rAPISystem = NULL;
	};
}