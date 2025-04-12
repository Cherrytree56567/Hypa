#include <iostream>
#include <chrono> <cmath>
#include <memory>
#include <DrizzleEngine.h>

int main() {
	Drizzle::App app;
	auto r3D = app.GetRendering3D();
	auto rAPI = app.GetRenderingAPISystem()->GetCurrentRenderingAPI();

	///r3D->LoadOBJ("Lost Empire", "dungeon.obj");
	r3D->LoadOBJ("Duck", "duck.obj");

	Drizzle::APIObject& duck = r3D->GetObject("Duck");

	rAPI->CreateTexture("DuckTex", "duck.png");

	//app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	//app.GetWindow()->GetFlags()->ChangeFlag("Height", 800);

	app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateShader("NewShader", "NewVert.spv", "NewFrag.spv");

	duck.textureName = "DuckTex";
	//cube.shaderName = "NewShader";

	while (app.Update()) {

	}
}