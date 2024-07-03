#include "Exec.h"

namespace Hypa {
	void Exec::AddFunction(std::string name, std::function<std::any(std::vector<std::any>)> func) {
		Functions.insert(std::make_pair(name, func));
	}

	std::any Exec::Execute(std::string name, std::vector<std::any> args) {
		return Functions[name](args);
	}
}