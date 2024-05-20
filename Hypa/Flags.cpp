#include "Flags.h"

namespace Hypa {
    Flags::Flags() {

    }

	void Flags::AddFlag(const std::string& name, std::variant<int*, double*, std::string*, bool*> variable) {
        flags[name] = variable;
    }

    void Flags::ChangeFlag(const std::string& name, std::variant<int, double, std::string, bool> value) {
        auto it = flags.find(name);
        if (it != flags.end()) {
            if (std::holds_alternative<int>(value)) {
                *(std::get<int*>(flags[name])) = std::get<int>(value);
            }
            else if (std::holds_alternative<double>(value)) {
                *(std::get<double*>(flags[name])) = std::get<double>(value);
            }
            else if (std::holds_alternative<std::string>(value)) {
                *(std::get<std::string*>(flags[name])) = std::get<std::string>(value);
            }
            else if (std::holds_alternative<bool>(value)) {
                *(std::get<bool*>(flags[name])) = std::get<bool>(value);
            }
        }
        else {
            std::cout << "Flag '" << name << "' not found." << std::endl;
        }
    }

    std::variant<int, double, std::string, bool> Flags::GetFlag(const std::string& name) {
        auto it = flags.find(name);
        if (it != flags.end()) {
            if (std::holds_alternative<int*>(it->second)) {
                return *std::get<int*>(it->second);
            }
            else if (std::holds_alternative<double*>(it->second)) {
                return *std::get<double*>(it->second);
            }
            else if (std::holds_alternative<std::string*>(it->second)) {
                return *std::get<std::string*>(it->second);
            }
            else if (std::holds_alternative<bool*>(it->second)) {
                return *std::get<bool*>(it->second);
            }
        }
        else {
            std::cout << "Flag '" << name << "' not found." << std::endl;
            return std::variant<int, double, std::string, bool>();
        }
    }
}