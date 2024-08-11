#include <iostream>
#include <chrono> <cmath>
#include <memory>
#include <HypaEngine.h>

int main() {
	Hypa::App app;
	bool ALT = false;
    bool LLL = false;
    float i = 0;

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

	app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateShader("NewShader", "NewVertex.glsl", "NewFragment.glsl");

	while (app.Update()) {
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved)) { ALT = true; }
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved) && ALT == true) {
			app.GetWindow()->GetFlags()->ChangeFlag("Width", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Width")) + 100);
			app.GetWindow()->GetFlags()->ChangeFlag("Height", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Height")) + 100);
			app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->ChangeShader("NewShader");
            LLL = true;
		}
        app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->DrawVerts(Squarevertices, Squareindices);
        app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->DrawVerts(Squareavertices, Squareaindices);

        if (LLL) {
            auto now = std::chrono::high_resolution_clock::now();
            auto duration = now.time_since_epoch();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
            float timeValue = static_cast<float>(milliseconds) / 1000.0f; // Convert milliseconds to seconds

            // Compute the color value based on the current time
            float colorValue = (std::sin(timeValue) + 1.0f) / 2.0f;   // Normalize to [0, 1] range

            // Update the uniform buffer object
            Hypa::UniformBufferObject& uni = app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->GetUniform(app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->GetCurrentShaderName());

            uni.CustomArgs.clear();
            uni.CustomArgs.push_back({ colorValue, "color" });

            app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->AddUniform(app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->GetCurrentShaderName(), uni);
        }
	}
}