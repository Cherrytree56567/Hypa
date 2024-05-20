#pragma once
#include "Window.h"

namespace Hypa {
	class App {
	public:
		HYPA_API App();

		HYPA_API bool Update();

		HYPA_API std::shared_ptr<Window> GetWindow();

	private:
		std::shared_ptr<Window> window;
	};
}