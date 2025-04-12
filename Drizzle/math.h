#pragma once
#include <glm/glm.hpp>
#include "RenderingAPI.h"

namespace Drizzle {
	bool is_outside_view(const glm::mat4& viewProj, const glm::vec3& center, float radius);
}