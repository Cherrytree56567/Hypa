#include <iostream>
#include <memory>
#include <HypaEngine.h>

int main() {
    using MyUBO = Hypa::UniformBufferObject<>;
	Hypa::App app;
	bool ALT = false;
    const std::vector<Hypa::Vertex> Squarevertices = {
            {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}
    };

    const std::vector<uint16_t> Squareindices = {
        0, 1, 2, 2, 3, 0
    };

    const std::vector<Hypa::Vertex> Squareavertices = {
        {{-0.5f, -0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}
    };

    const std::vector<uint16_t> Squareaindices = {
        0, 1, 2, 2, 3, 0
    };

	app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	app.GetWindow()->GetFlags()->ChangeFlag("Height", 400);

	app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateShader("NewShader", "NewVert.spv", "NewFrag.spv");

	while (app.Update()) {
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved)) { ALT = true; }
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved) && ALT == true) {
			app.GetWindow()->GetFlags()->ChangeFlag("Width", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Width")) + 100);
			app.GetWindow()->GetFlags()->ChangeFlag("Height", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Height")) + 100);
			app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->ChangeShader("NewShader");
		}
        app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->DrawVerts(Squarevertices, Squareindices);
        app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->DrawVerts(Squareavertices, Squareaindices);

        MyUBO ubo = {};

        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        ubo.proj = glm::perspective(glm::radians(45.0f), std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Width")) / (float)std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Height")), 0.1f, 10.0f);

        ubo.proj[1][1] *= -1;

        app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->updateUniform(ubo);
	}
}