#include "OpenGL.h"

namespace Drizzle {
    const char* readFile(const char* filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file) {
            std::cerr << "[Drizzle::Core] Error: Could not open file: " << filename << std::endl;
            return nullptr;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        char* buffer = new char[size + 1];

        if (!file.read(buffer, size)) {
            std::cerr << "[Drizzle::Core] Error: Could not read file: " << filename << std::endl;
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
            std::cout << "[Drizzle::Core] Error: Failed to initialize GLAD\n";
            exit(-1);
        }

        //CreateShader("Default", "vertex.glsl", "fragment.glsl");
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
            std::cout << "[Drizzle::Core] Error: Vertex Shader Compilation Failed:\n" << infoLog << std::endl;
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
            std::cout << "[Drizzle::Core] Error: Fragment Shader Compilation Failed:\n" << infoLoga << std::endl;
        }

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successa);
        if (!successa) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "[Drizzle::Core] Error: Failed to link shaders: \n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        Shaders.insert(std::make_pair(name, std::make_tuple(shaderProgram, shaderProgram)));
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

    PushConstants& OpenGL::GetPushConstants() {
        return pc;
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