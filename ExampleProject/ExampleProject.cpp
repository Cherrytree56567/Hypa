#include <iostream>
#include <chrono> <cmath>
#include <memory>
#include <DrizzleEngine.h>

int main() {
	Drizzle::App app;
	bool ALT = false;
    bool LLL = false;
    float i = 0;
	auto cube = Drizzle::LoadObjFile("lost_empire.obj");
	auto duck = Drizzle::LoadObjFile("duck.obj");

	app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateTexture("DuckTex", "duck.png");

	//app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	//app.GetWindow()->GetFlags()->ChangeFlag("Height", 800);

	//app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateShader("NewShader", "NewVertex.glsl", "NewFragment.glsl");

	duck.textureName = "DuckTex";

	app.GetRendering3D()->CreateObject("Cube", cube);
	app.GetRendering3D()->CreateObject("Duck", duck);

	while (app.Update()) {

	}
}