#include <iostream>
#include <chrono> <cmath>
#include <memory>
#include <DrizzleEngine.h>

int main() {
	Drizzle::App app;
	bool ALT = false;
    bool LLL = false;
    float i = 0;
	auto cube = Drizzle::LoadObjFile("cube.obj");
	auto duck = Drizzle::LoadObjFile("duck.obj");

	//app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	//app.GetWindow()->GetFlags()->ChangeFlag("Height", 800);

	//app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateShader("NewShader", "NewVertex.glsl", "NewFragment.glsl");

	app.GetRendering3D()->CreateObject("Cube", cube.first, cube.second);
	app.GetRendering3D()->CreateObject("Duck", duck.first, duck.second);

	while (app.Update()) {

	}
}