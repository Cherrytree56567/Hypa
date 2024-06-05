#include <iostream>
#include <memory>
#include <HypaEngine.h>

int main() {
	Hypa::App app;
	bool ALT = false;

	app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	app.GetWindow()->GetFlags()->ChangeFlag("Height", 400);

	app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->CreateShader("NewShader", "NewVert.spv", "NewFrag.spv");
	app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->ChangeShader("Default");

	while (app.Update()) {
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved)) { ALT = true; }
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved) && ALT == true) {
			app.GetWindow()->GetFlags()->ChangeFlag("Width", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Width")) + 100);
			app.GetWindow()->GetFlags()->ChangeFlag("Height", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Height")) + 100);
			app.GetRenderingAPISystem()->GetCurrentRenderingAPI()->ChangeShader("NewShader");
		}
	}
}