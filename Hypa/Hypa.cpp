#include "App.h"

int main() {
	Hypa::App application;

	int wid = 0;

	while (application.Update()) {
		wid += 1;
		application.GetWindow()->GetFlags()->ChangeFlag("Width", wid);
		application.GetWindow()->GetFlags()->ChangeFlag("Height", wid);
	}
}
