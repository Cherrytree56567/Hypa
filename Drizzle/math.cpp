#include "math.h"

/*
* TODO: Add transforms to the object and compute the AABB in world space.
* Also add Frustrum Culling.
*/

namespace Drizzle {
    bool is_visible(const APIObject& obj, const glm::mat4& viewproj) {
        std::array<glm::vec3, 8> corners{
            glm::vec3{ 1,  1,  1 },
            glm::vec3{ 1,  1, -1 },
            glm::vec3{ 1, -1,  1 },
            glm::vec3{ 1, -1, -1 },
            glm::vec3{-1,  1,  1 },
            glm::vec3{-1,  1, -1 },
            glm::vec3{-1, -1,  1 },
            glm::vec3{-1, -1, -1 },
        };

        // Combine view-projection and object transform.
        glm::mat4 matrix = viewproj * obj.transform;

        // Initialize min/max for the clip-space bounding box.
        glm::vec3 minClip{ 1.5f, 1.5f, 1.5f };
        glm::vec3 maxClip{ -1.5f, -1.5f, -1.5f };

        for (int c = 0; c < 8; c++) {
            // For each corner of the OBB, compute its world-space corner:
            glm::vec4 v = matrix * glm::vec4(obj.bounds.origin + (corners[c] * obj.bounds.extents), 1.f);
            // Perspective division.
            v.x /= v.w;
            v.y /= v.w;
            v.z /= v.w;

            minClip = glm::min(glm::vec3{ v.x, v.y, v.z }, minClip);
            maxClip = glm::max(glm::vec3{ v.x, v.y, v.z }, maxClip);
        }

        // For Vulkan, x,y clip coordinates are in [-1,1] and z in [0,1].
        // If the clip-space bounding box is entirely outside, then the object is invisible.
        if (minClip.z > 1.f || maxClip.z < 0.f ||
            minClip.x > 1.f || maxClip.x < -1.f ||
            minClip.y > 1.f || maxClip.y < -1.f)
        {
            return false;
        }
        else {
            return true;
        }
    }

}