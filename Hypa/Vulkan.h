#pragma once
#include "base.h"
#include "RenderingAPI.h"

namespace Hypa {
	class Vulkan : public RenderingAPI {
	public:
		HYPA_API Vulkan();

		HYPA_API void OnAttach() override;
		HYPA_API void OnDetach() override;
		HYPA_API void Render() override;

		HYPA_API const std::string& GetName() const override;

	private:
		Flags flags;
		std::string name;
	};
}