#include "Lighting.h"

namespace Drizzle {
	Light PointLight::GetLight() const {
		return Light{ position, intensity, color, radius, glm::vec3(0.0f), 0.0f, 0.0f, static_cast<int>(LightType::Point) };
	}

	Light DirectionalLight::GetLight() const {
		return Light{ {0.0f, 0.0f, 0.0f}, intensity, color, 0.0f, direction, 0.0f, 0.0f, static_cast<int>(LightType::Directional) };
	}

	Light SpotLight::GetLight() const {
		return Light{ position, intensity, color, 0.0f, direction, innerAngle, outerAngle, static_cast<int>(LightType::Spot) };
	}

	Light AreaLight::GetLight() const {
		return Light{ position, intensity, color, 0.0f, direction, 0.0f, 0.0f, static_cast<int>(LightType::Area) };
	}
}