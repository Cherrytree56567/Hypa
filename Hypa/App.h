#pragma once
#include "Window.h"

namespace Hypa {
	class App {
	public:
		App();

		bool Update();

	private:
		std::shared_ptr<Window> window;
	};
}