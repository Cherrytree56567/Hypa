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

	void Rendering3D::DrawObject(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
		rAPISystem->GetCurrentRenderingAPI()->DrawVerts(vertices, indices);
	}

    std::pair<std::vector<float>, std::vector<unsigned int>> LoadObjFile(const std::string& filePath) {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "Error loading OBJ file: " << importer.GetErrorString() << std::endl;
            return std::make_pair(vertices, indices);
        }

        const aiMesh* mesh = scene->mMeshes[0]; // Assuming there is only one mesh in the scene

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            // Vertex position (x, y, z)
            vertices.push_back(mesh->mVertices[i].x);
            vertices.push_back(mesh->mVertices[i].y);
            vertices.push_back(mesh->mVertices[i].z);

            // Texture coordinates (u, v)
            if (mesh->mTextureCoords[0]) {
                vertices.push_back(mesh->mTextureCoords[0][i].x);
                vertices.push_back(mesh->mTextureCoords[0][i].y);
            }
            else {
                // If the model doesn't have texture coordinates, use default values
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
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