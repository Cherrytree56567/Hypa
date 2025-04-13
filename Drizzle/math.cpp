#include "math.h"

namespace Drizzle {
    glm::vec3 TransformPoint(const glm::mat4& mat, const glm::vec3& v) {
        glm::vec4 transformed = mat * glm::vec4(v, 1.0f);
        return glm::vec3(transformed) / transformed.w;
    }

    std::array<glm::vec3, 8> GetBoxCorners(const glm::vec3& min, const glm::vec3& max) {
        return {
            glm::vec3{min.x, min.y, min.z},
            glm::vec3{max.x, min.y, min.z},
            glm::vec3{min.x, max.y, min.z},
            glm::vec3{max.x, max.y, min.z},
            glm::vec3{min.x, min.y, max.z},
            glm::vec3{max.x, min.y, max.z},
            glm::vec3{min.x, max.y, max.z},
            glm::vec3{max.x, max.y, max.z}
        };
    }

    bool IsBoxVisible(const glm::vec3& minBound, const glm::vec3& maxBound, const glm::mat4& model, const glm::mat4& viewProj) {
        auto corners = GetBoxCorners(minBound, maxBound);

        int outside[6] = { 0, 0, 0, 0, 0, 0 };

        for (const auto& corner : corners) {
            glm::vec4 local = { corner.x, corner.y, corner.z, 1.0f };
            glm::vec4 world = model * local;
            glm::vec4 clip = viewProj * world;

            if (clip.w == 0.0f) continue;
            float x = clip.x / clip.w;
            float y = clip.y / clip.w;
            float z = clip.z / clip.w;

            if (x < -1) outside[0]++; 
            if (x > 1) outside[1]++; 
            if (y < -1) outside[2]++; 
            if (y > 1) outside[3]++; 
            if (z < -1) outside[4]++; 
            if (z > 1) outside[5]++; 
        }

        for (int i = 0; i < 6; ++i)
            if (outside[i] == 8)
                return false;

        return true;
    }
}