#include "Skybox.h"

namespace Drizzle {
	void CreateSphere(APIObject& obj, float radius, int rings, int segments) {
		obj.vertices.clear();
		obj.indices.clear();

		glm::vec3 normal;
		glm::vec4 color = glm::vec4(1.0f);

		for (int y = 0; y <= rings; ++y) {
			float v = static_cast<float>(y) / rings;
			float theta = v * glm::pi<float>(); // From 0 to PI

			for (int x = 0; x <= segments; ++x) {
				float u = static_cast<float>(x) / segments;
				float phi = u * glm::two_pi<float>(); // From 0 to 2PI

				float px = radius * sin(theta) * cos(phi);
				float py = radius * cos(theta);
				float pz = radius * sin(theta) * sin(phi);

				glm::vec3 pos(px, py, pz);
				glm::vec3 norm = glm::normalize(pos);

				obj.vertices.push_back(Vertex{
					pos,
					u,
					norm,
					v,
					color
					});
			}
		}

		for (int y = 0; y < rings; ++y) {
			for (int x = 0; x < segments; ++x) {
				int i0 = y * (segments + 1) + x;
				int i1 = i0 + 1;
				int i2 = i0 + (segments + 1);
				int i3 = i2 + 1;

				// Two triangles per quad
				obj.indices.push_back(i0);
				obj.indices.push_back(i2);
				obj.indices.push_back(i1);

				obj.indices.push_back(i1);
				obj.indices.push_back(i2);
				obj.indices.push_back(i3);
			}
		}

		obj.minBound = glm::vec3(-radius);
		obj.maxBound = glm::vec3(radius);
	}

	Skybox::Skybox(std::shared_ptr<App> app, std::string texturePath) : texturePath(texturePath), app(app) {
		this->texturePath = texturePath;

		app->GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateTexture("SkyboxTex", texturePath);

		APIObject obj;
		obj.name = "SkyBox";
		obj.groupName = "SkyBox";
		obj.textureName = "SkyboxTex";

		obj.modelMatrix = glm::mat4(1.0f);

		CreateSphere(obj, 100.0f, 32, 64);

		app->GetRendering3D()->CreateObject(obj.name, obj);

		app->GetEventSystem()->AddEventListener(EventType::AppRender, [](std::shared_ptr<Event> event, std::any a) {
			auto ts = std::any_cast<Skybox*>(a);

			// Get the camera's view matrix
			glm::mat4 viewMatrix = ts->app->GetRendering3D()->GetCurrentCamera().GetViewMatrix();

			// Invert the view matrix to get the camera's world transform
			glm::mat4 invViewMatrix = glm::inverse(viewMatrix);

			// Extract the camera world position from the inverse view matrix
			glm::vec3 cameraPosition = glm::vec3(invViewMatrix[3]);

			// Set the skybox's model matrix to a translation at the camera's position
			ts->app->GetRendering3D()->Getobject("SkyBox").modelMatrix = glm::translate(glm::mat4(1.0f), cameraPosition);

		}, this);
	}

	Skybox::~Skybox() {
		// Cleanup code if needed
	}

	void Skybox::LoadSkybox(std::string texturePath) {
		this->texturePath = texturePath;

		app->GetRenderingAPISystem()->GetCurrentRenderingAPI()->RemoveTexture("SkyboxTex");
		app->GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateTexture("SkyboxTex", texturePath);
		
		APIObject obj;
		obj.name = "SkyBox";
		obj.groupName = "SkyBox";
		obj.textureName = "SkyboxTex";

		obj.modelMatrix = glm::mat4(1.0f);

		CreateSphere(obj, 100.0f, 32, 64);

		app->GetRendering3D()->CreateObject(obj.name, obj);
	}
}