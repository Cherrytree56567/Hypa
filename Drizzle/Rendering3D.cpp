#include "Rendering3D.h"

namespace Drizzle {
	Rendering3D::~Rendering3D() {

	}

	Rendering3D::Rendering3D(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys) : name("3DLayer"), pWindow(window), rAPISystem(rAPIsys), show(true) {
		cameras["Default"] = rAPISystem->GetCurrentRenderingAPI()->GetPushConstants().worldMatrix;
	}

	void Rendering3D::OnAttach() {

	}

	void Rendering3D::OnDetach() {

	}

    void Rendering3D::Render() {
		if (show) {
			rAPISystem->GetCurrentRenderingAPI()->GetPushConstants().worldMatrix = cameras[CurrentCamera].GetMatrix();
			rAPISystem->GetCurrentRenderingAPI()->Render3D(objects, lights);
		}
	}

	bool Rendering3D::IsShown() const {
		return show;
	}

	const std::string& Rendering3D::GetName() const {
		return name;
	}

	void Rendering3D::SetShow(bool value) {
		show = value;
	}

	void Rendering3D::CreateObject(std::string name, APIObject obj) {
		obj.name = name;
		obj.groupName = name;
        rAPISystem->GetCurrentRenderingAPI()->AddObject(obj);
		objects.push_back(obj);
	}

    void Rendering3D::LoadOBJ(std::string name, const std::string& filePath, const std::string& mtlPath) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
		bool MtlExists = false;

        if (!scene || !scene->HasMeshes()) {
            log.Error("Couldn't load OBJ file: " + std::string(importer.GetErrorString()));
			return;
        }

		std::ifstream objFile(filePath.c_str());

		std::string line;
		while (std::getline(objFile, line)) {
			if (line.rfind("mtllib ", 0) == 0) {
				MtlExists = true;
			}
		}

		if (MtlExists) {
			for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
				const aiMaterial* mat = scene->mMaterials[i];

				aiString texPathKd;
				aiString texname;

				mat->Get(AI_MATKEY_NAME, texname);
				mat->GetTexture(aiTextureType_DIFFUSE, 0, &texPathKd);

				if (rAPISystem->GetCurrentRenderingAPI()->TextureExists(std::string(texPathKd.C_Str()))) {
					continue;
				}
				rAPISystem->GetCurrentRenderingAPI()->CreateTexture(std::string(texPathKd.C_Str()), texPathKd.C_Str());
			}
		}

		for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
			std::vector<Vertex> vertices;
			std::vector<uint16_t> indices;

			const aiMesh* mesh = scene->mMeshes[i];
			const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::string texture;

			for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
				Vertex vertex;

				vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

				if (mesh->mTextureCoords[0]) {
					vertex.uv_x = mesh->mTextureCoords[0][i].x;
					vertex.uv_y = mesh->mTextureCoords[0][i].y;
				} else {
					vertex.uv_x = 0.0f;
					vertex.uv_y = 0.0f;
				}

				vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
				vertex.color = { 0.5, 0.5, 0.5, 1 };

				vertices.push_back(vertex);
			}

			glm::vec3 minBound = { FLT_MAX, FLT_MAX, FLT_MAX };
			glm::vec3 maxBound = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

			for (const auto& v : vertices) {
				if (v.position.x < minBound.x) minBound.x = v.position.x;
				if (v.position.y < minBound.y) minBound.y = v.position.y;
				if (v.position.z < minBound.z) minBound.z = v.position.z;

				if (v.position.x > maxBound.x) maxBound.x = v.position.x;
				if (v.position.y > maxBound.y) maxBound.y = v.position.y;
				if (v.position.z > maxBound.z) maxBound.z = v.position.z;
			}

			glm::vec3 center = {
				(minBound.x + maxBound.x) / 2.0f,
				(minBound.y + maxBound.y) / 2.0f,
				(minBound.z + maxBound.z) / 2.0f
			};

			for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
				const aiFace& face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; ++j) {
					indices.push_back(face.mIndices[j]);
				}
			}

			APIObject obj;
			obj.indices = indices;
			obj.vertices = vertices;
			obj.minBound = minBound;
			obj.maxBound = maxBound;
			obj.center = center;

			if (MtlExists) {
				aiString texPath;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS) {
					texture = texPath.C_Str();
				}
				obj.textureName = std::string(texture);
			}

			if (scene->mNumMeshes > 1) {
				obj.name = filePath + "_" + std::to_string(i);
				obj.groupName = name;
			} else {
				obj.name = name;
				obj.groupName = name;
			}

			objects.push_back(obj);
			rAPISystem->GetCurrentRenderingAPI()->AddObject(obj);
		}
    }

	void Rendering3D::RemoveObject(std::string name, bool grouped) {
		if (grouped) {
			for (size_t i = 0; i < objects.size(); i++) {
				if (objects[i].groupName == name) {
					rAPISystem->GetCurrentRenderingAPI()->RemoveObject(objects[i].name);
					objects.erase(objects.begin() + i);
					i--;
				}
			}
		} else {
			for (auto it = objects.begin(); it != objects.end(); ++it) {
				if (it->name == name) {
					rAPISystem->GetCurrentRenderingAPI()->RemoveObject(name);
					objects.erase(it);
					break;
				}
			}
		}
	}

	APIObject& Rendering3D::GetObject(std::string name) {
		for (auto it = objects.begin(); it != objects.end(); ++it) {
			if (it->name == name) {
				return *it;
			}
		}
	}

	void Rendering3D::AddCamera(std::string name, Camera camera) {
		cameras[name] = camera;
	}

	void Rendering3D::RemoveCamera(std::string name) {
		cameras.erase(name);
	}

	Camera& Rendering3D::GetCamera(std::string name) {
		return cameras[name];
	}

	Camera& Rendering3D::GetCurrentCamera() {
		return cameras[CurrentCamera];
	}

	void Rendering3D::SetCurrentCamera(std::string name) {
		CurrentCamera = name;
	}

	void Rendering3D::AddLight(Lighting light) {
		lights.push_back(light);
	}

	void Rendering3D::RemoveLight(std::string name) {
		for (auto it = lights.begin(); it != lights.end(); ++it) {
			if (it->getName() == name) {
				lights.erase(it);
				break;
			}
		}
	}

	Lighting& Rendering3D::GetLight(std::string name) {
		for (auto it = lights.begin(); it != lights.end(); ++it) {
			if (it->getName() == name) {
				return *it;
			}
		}
	}
}