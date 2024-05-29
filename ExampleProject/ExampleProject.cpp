#include <iostream>
#include <memory>
#include <HypaEngine.h>

int main() {
	Hypa::App app;

	app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	app.GetWindow()->GetFlags()->ChangeFlag("Height", 400);

	while (app.Update()) {
		if (app.GetEventSystem()->isUnhandledEvent(Hypa::EventType::WindowMoved)) {
			app.GetWindow()->GetFlags()->ChangeFlag("Width", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Width")) + 100);
			app.GetWindow()->GetFlags()->ChangeFlag("Height", std::get<int>(app.GetWindow()->GetFlags()->GetFlag("Height")) + 100);
		}
	}
}