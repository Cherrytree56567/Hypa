#pragma once
#include <glm/glm.hpp>
#include <array>

namespace Drizzle {
    glm::vec3 TransformPoint(const glm::mat4& mat, const glm::vec3& v);
    std::array<glm::vec3, 8> GetBoxCorners(const glm::vec3& min, const glm::vec3& max);
    bool IsBoxVisible(const glm::vec3& minBound, const glm::vec3& maxBound, const glm::mat4& model, const glm::mat4& viewProj);
}