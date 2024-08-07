#include <iostream>
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

	//app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateShader("NewShader", "NewVert.spv", "NewFrag.spv");

	while (app.Update()) {
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved)) { ALT = true; }
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved) && ALT == true) {
			app.GetWindow()->GetFlags()->ChangeFlag("Width", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Width")) + 100);
			app.GetWindow()->GetFlags()->ChangeFlag("Height", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Height")) + 100);
			//app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->ChangeShader("NewShader");
            LLL = true;
		}
        /*app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->DrawVerts(Squarevertices, Squareindices);
        app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->DrawVerts(Squareavertices, Squareaindices);

        if (LLL) {
            Hypa::UniformBufferObject uni;

            uni.CustomArgs.push_back(i);

            app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->AddUniform("NewShader", uni);

            i += 0.01;
            std::cout << app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->GetCurrentShaderName();
        }*/
	}
}