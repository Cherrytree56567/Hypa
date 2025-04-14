#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <filesystem>
#include "Camera.h"
#include "base.h"
#include "Layer.h"
#include "Lighting.h"

namespace Drizzle {
	class Rendering3D : public Layer {
    public:
        Drizzle_API Rendering3D(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys);

        Drizzle_API virtual ~Rendering3D() override;
        Drizzle_API virtual void OnAttach() override;
        Drizzle_API virtual void OnDetach() override;
        Drizzle_API virtual void Render() override;

        Drizzle_API virtual bool IsShown() const override;
        Drizzle_API virtual const std::string& GetName() const override;
        Drizzle_API virtual void SetShow(bool value) override;

        Drizzle_API void CreateObject(std::string name, APIObject obj);
		Drizzle_API void RemoveObject(std::string name, bool grouped = false);
        Drizzle_API APIObject& GetObject(std::string name);
        Drizzle_API void LoadOBJ(std::string name, const std::string& filePath, const std::string& mtlPath = "");

		Drizzle_API void AddCamera(std::string name, Camera camera);
		Drizzle_API void RemoveCamera(std::string name);
		Drizzle_API Camera& GetCamera(std::string name);
        Drizzle_API Camera& GetCurrentCamera();
		Drizzle_API void SetCurrentCamera(std::string name);
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
        std::shared_ptr<RenderingAPISystem> rAPISystem = NULL;
        std::map<std::string, Camera> cameras;
		std::string CurrentCamera = "Default";
        std::vector<Lighting> lights;
        std::vector<APIObject> objects;
        Logging log;
	};
}