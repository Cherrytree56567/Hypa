#include <iostream>
#include <HypaEngine.h>

int main() {
	Hypa::App app;

	app.GetWindow()->GetFlags()->ChangeFlag("Width", 800);
	app.GetWindow()->GetFlags()->ChangeFlag("Height", 400);

	while (app.Update()) {

	}
}