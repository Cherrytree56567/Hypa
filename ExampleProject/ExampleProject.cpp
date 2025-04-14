#include <iostream>
#include <chrono> <cmath>
#include <memory>
#include <DrizzleEngine.h>

int main() {
	Drizzle::App app;
	auto r3D = app.GetRendering3D();
	auto rAPI = app.GetRenderingAPISystem()->GetCurrentRenderingAPI();

	r3D->LoadOBJ("Buildings", "buildings.obj");
	r3D->LoadOBJ("Duck", "duck.obj");

	Drizzle::APIObject& duck = r3D->GetObject("Duck");

	rAPI->CreateTexture("DuckTex", "ios.png");

	//app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	//app.GetWindow()->GetFlags()->ChangeFlag("Height", 800);

	app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateShader("NewShader", "NewVert.spv", "NewFrag.spv");

	duck.textureName = "DuckTex";

	r3D->GetCurrentCamera().MoveTo(glm::vec3(0.0f, -50.0f, 0.0f));

	while (app.Update()) {
		r3D->GetCurrentCamera().AddMoveTo(glm::vec3(0.1f, 0.0f, 0.0f));
	}
}