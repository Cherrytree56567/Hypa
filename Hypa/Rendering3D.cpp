#include "Rendering3D.h"

namespace Hypa {
	Rendering3D::~Rendering3D() {

	}

	Rendering3D::Rendering3D(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys) : name("3DLayer"), pWindow(window), rAPISystem(rAPIsys), show(true) {
	}

	void Rendering3D::OnAttach() {
	}

	void Rendering3D::OnDetach() {

	}

    void Rendering3D::Render() {
        rAPISystem->GetCurrentRenderingAPI()->Render();
        for (auto obj : Objects) {
            rAPISystem->GetCurrentRenderingAPI()->DrawVerts(obj.second.vertices, obj.second.indices);
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

	void Rendering3D::CreateObject(std::string name, std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
        Objects.push_back({ name, { vertices, indices } });
	}

    std::pair<std::vector<Vertex>, std::vector<uint16_t>> LoadObjFile(const std::string& filePath) {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "Error loading OBJ file: " << importer.GetErrorString() << std::endl;
            return std::make_pair(vertices, indices);
        }

        const aiMesh* mesh = scene->mMeshes[0];

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            Vertex vertex;

            vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

            if (mesh->mTextureCoords[0]) {
                vertex.TexCoords = glm::vec3(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, 0.0f);
            }
            else {
                vertex.TexCoords = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            vertex.Normals = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }

        return std::make_pair(vertices, indices);
    }
}