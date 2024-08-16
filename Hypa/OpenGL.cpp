#include "OpenGL.h"

namespace Hypa {
    const char* readFile(const char* filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file) {
            std::cerr << "[Hypa::Core] Error: Could not open file: " << filename << std::endl;
            return nullptr;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        char* buffer = new char[size + 1];

        if (!file.read(buffer, size)) {
            std::cerr << "[Hypa::Core] Error: Could not read file: " << filename << std::endl;
            delete[] buffer;
            return nullptr;
        }

        buffer[size] = '\0';

        return buffer;
    }

	OpenGL::OpenGL(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events) {
		name = "OpenGL";
		pWindow = window;
		pEvents = Events;
	}

    void OpenGL::OnAttach() {
        pWindow->UseGLFW();

        if (!gladLoadGL()) {
            std::cout << "[Hypa::Core] Error: Failed to initialize GLAD\n";
            exit(-1);
        }

        CreateShader("Default", "vertex.glsl", "fragment.glsl");
        ChangeShader("Default");

        ShaderChanged = true;

        //CreateUniformBuffer("Default");
	}

	void OpenGL::OnDetach() {
		pWindow->UseNoClientApi();
	}

    void OpenGL::Render() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

	void OpenGL::CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {
        const char* vertexShaderSource = readFile(VertShaderPath.c_str());
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "[Hypa::Core] Error: Vertex Shader Compilation Failed:\n" << infoLog << std::endl;
        }

        const char* fragmentShaderSource = readFile(FragShaderPath.c_str());
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        int successa;
        char infoLoga[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successa);
        if (!successa) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLoga);
            std::cout << "[Hypa::Core] Error: Fragment Shader Compilation Failed:\n" << infoLoga << std::endl;
        }

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successa);
        if (!successa) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "[Hypa::Core] Error: Failed to link shaders: \n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        UniformBufferObject uni;

        Shaders.insert(std::make_pair(name, std::make_tuple(shaderProgram, shaderProgram, uni)));
        AddUniform(name, uni);
	}

	void OpenGL::RemoveShader(std::string name) {
        auto it = Shaders.find(name);
        if (it != Shaders.end()) {
            Shaders.erase(it);
        } else {
            std::cout << name << " not found in the map." << std::endl;
        }
	}

	void OpenGL::ChangeShader(std::string name) {
        CurrentShaderName = name;
        ShaderChanged = true;
	}

	std::string OpenGL::GetCurrentShaderName() {
		return CurrentShaderName;
	}

    void OpenGL::DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
        GLuint CurrentVertexArray, CurrentVertexBuffer, CurrentIndexBuffer;
        glGenVertexArrays(1, &CurrentVertexArray);
        glGenBuffers(1, &CurrentVertexBuffer);
        glGenBuffers(1, &CurrentIndexBuffer);
        //
        glBindVertexArray(CurrentVertexArray);

        glBindBuffer(GL_ARRAY_BUFFER, CurrentVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // Vertex Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glEnableVertexAttribArray(0);

        // Texture Coordinates
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glEnableVertexAttribArray(1);

        // Normals
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normals));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CurrentIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

        glBindVertexArray(CurrentVertexArray);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);

        VertexArray.push_back(CurrentVertexArray);
        VertexBuffer.push_back(CurrentVertexBuffer);
        IndexBuffer.push_back(CurrentIndexBuffer);
        Indices.push_back(indices);
    }

	void OpenGL::AddUniform(std::string name, UniformBufferObject& ubo) {
        GLuint shaderProgram = std::get<0>(GetShader(GetCurrentShaderName()));
        glUseProgram(shaderProgram);
        Shaders[name] = std::make_tuple(std::get<0>(Shaders[name]), std::get<1>(Shaders[name]), ubo);

        GLuint viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
        GLuint projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
        GLuint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");

        glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(ubo.view));
        glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(ubo.proj));
        glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(ubo.model));

        for (const auto& [value, uniformName] : ubo.CustomArgs) {
            GLuint uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());

            std::visit([&](auto&& val) {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, int>) {
                    glUniform1i(uniformLocation, val);
                }
                else if constexpr (std::is_same_v<T, float>) {
                    glUniform1f(uniformLocation, val);
                }
                else if constexpr (std::is_same_v<T, double>) {
                    glUniform1d(uniformLocation, val);
                }
                else if constexpr (std::is_same_v<T, glm::mat2>) {
                    glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat2x2>) {
                    glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat2x3>) {
                    glUniformMatrix2x3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat2x4>) {
                    glUniformMatrix2x4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat3>) {
                    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat3x2>) {
                    glUniformMatrix3x2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat3x3>) {
                    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat3x4>) {
                    glUniformMatrix3x4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat4>) {
                    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat4x2>) {
                    glUniformMatrix4x2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat4x3>) {
                    glUniformMatrix4x3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::mat4x4>) {
                    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::vec1>) {
                    glUniform1fv(uniformLocation, 1, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::vec2>) {
                    glUniform2fv(uniformLocation, 1, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::vec3>) {
                    glUniform3fv(uniformLocation, 1, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, glm::vec4>) {
                    glUniform4fv(uniformLocation, 1, glm::value_ptr(val));
                }
                else if constexpr (std::is_same_v<T, unsigned int>) {
                    glUniform1ui(uniformLocation, val);
                }
                else if constexpr (std::is_same_v<T, char*>) {
                    glUniform1i(uniformLocation, *reinterpret_cast<int*>(val));
                }
                else if constexpr (std::is_same_v<T, std::string>) {
                    glUniform1i(uniformLocation, std::stoi(val));
                }
                }, value);
        }
	}

    UniformBufferObject& OpenGL::GetUniform(std::string name) {
        return std::get<2>(Shaders[name]);
    }

    std::tuple<unsigned int, unsigned int, UniformBufferObject> OpenGL::GetShader(std::string name) {
        return Shaders[name];
    }

    void OpenGL::CreateTexture(std::string name, std::string TexturePath) {

    }

    void OpenGL::RemoveTexture(std::string name) {
        auto it = Textures.find(name);
        if (it != Textures.end()) {
            Textures.erase(it);
        }
        else {
            std::cout << name << " not found in the map." << std::endl;
        }
    }

    void OpenGL::ChangeTexture(std::string name) {

    }

    std::string OpenGL::GetCurrentTextureName() {
        return CurrentTextureName;
    }
}