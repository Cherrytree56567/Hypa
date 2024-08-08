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
	}

	void OpenGL::OnDetach() {
		pWindow->UseNoClientApi();
	}

    void OpenGL::Render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        std::vector<Vertex> vertices = {
            {{-0.5f, -0.5f, 0.0f}, {0.0, 0.0, 0.0}}, // left
            {{0.5f, -0.5f, 0.0f}, {0.0, 0.0, 0.0}}, // right
            {{ 0.0f, 0.5f, 0.0f}, {0.0, 0.0, 0.0}}  // top
        };

        std::vector<uint16_t> indices = {
            0, 1, 2
        };

        DrawVerts(vertices, indices);

        glUseProgram(std::get<0>(GetShader(GetCurrentShaderName())));
        for (int i = 0; i < VertexArray.size(); i++) {
            glBindVertexArray(VertexArray[i]);
            glDrawElements(GL_TRIANGLES, Indices[i].size(), GL_UNSIGNED_SHORT, 0);
        }

        VertexArray.clear();
        VertexBuffer.clear();
        IndexBuffer.clear();
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

        Shaders.insert(std::make_pair(name, std::make_tuple(shaderProgram, shaderProgram, UniformBufferObject())));
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

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CurrentIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

        VertexArray.push_back(CurrentVertexArray);
        VertexBuffer.push_back(CurrentVertexBuffer);
        IndexBuffer.push_back(CurrentIndexBuffer);
        Indices.push_back(indices);
    }

	void OpenGL::AddUniform(std::string name, UniformBufferObject& ubo) {
        Shaders[name] = std::make_tuple(std::get<0>(Shaders[name]), std::get<1>(Shaders[name]), ubo);
	}

    std::tuple<unsigned int, unsigned int, UniformBufferObject> OpenGL::GetShader(std::string name) {
        return Shaders[name];
    }
}