#include <iostream>
#include <chrono> <cmath>
#include <memory>
#include <DrizzleEngine.h>

int main() {
	std::shared_ptr<Drizzle::App> app = std::make_shared<Drizzle::App>();
	Drizzle::FirstPersonController fpc(app);
	auto r3D = app->GetRendering3D();
	auto rAPI = app->GetRenderingAPISystem()->GetCurrentRenderingAPI();

	Drizzle::Skybox sky(app, "SkyBox.png");

	std::shared_ptr<Drizzle::PointLight> mainLight = std::make_shared<Drizzle::PointLight>("Main", glm::vec3(-25.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f, 10.0f);

	r3D->LoadOBJ("Buildings", "buildings.obj");
	r3D->LoadOBJ("Duck", "duck.obj");

	Drizzle::APIObject& duck = r3D->Getobject("Duck");

	rAPI->CreateTexture("DuckTex", "ios.png");

	//app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	//app.GetWindow()->GetFlags()->ChangeFlag("Height", 800);

	rAPI->CreateShader("NewShader", "NewVert.spv", "NewFrag.spv");

	duck.textureName = "DuckTex";

	r3D->AddLight(mainLight);

	r3D->GetCurrentCamera().MoveTo(glm::vec3(0.0f, 0.0f, 0.0f));

	fpc.SetSpeed(1.0f);

	while (app->Update()) {

	}

	return 0;
}