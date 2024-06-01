#pragma once
#include "base.h"
#include "Flags.h"

namespace Hypa {
	class RenderingAPI {
	public:
		HYPA_API RenderingAPI() {}

		HYPA_API virtual void OnAttach() { }
		HYPA_API virtual void OnDetach() { }
		HYPA_API virtual void Render() { }

		HYPA_API virtual const std::string& GetName() const { return name; }

	private:
		Flags flags;
		std::string name;
	};

	class RenderingAPISystem {
	public:
		HYPA_API RenderingAPISystem() {}

		HYPA_API void AddAPI(std::shared_ptr<RenderingAPI> API);
		HYPA_API void RemoveAPIByName(const std::string& name);

	private:
		std::vector<std::shared_ptr<RenderingAPI>> renderingAPIS;
	};
}