#include <iostream>
#include <HypaEngine.h>

int main() {
	Hypa::App app;

	int wid = 0;

	while (app.Update()) {
		wid += 1;
		app.GetWindow()->GetFlags()->ChangeFlag("Width", wid);
		app.GetWindow()->GetFlags()->ChangeFlag("Height", wid);
	}
}