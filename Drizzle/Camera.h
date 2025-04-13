#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "base.h"

namespace Drizzle {
    enum class ProjectionType {
        Perspective,
        Orthographic
    };

    class Camera {
    public:
        Drizzle_API Camera(glm::mat4* externalProjectionMatrix);

        Drizzle_API void MoveTo(const glm::vec3& newPos);
        Drizzle_API void LookAt(const glm::vec3& target);
        Drizzle_API void SetUp(const glm::vec3& newUp);

        Drizzle_API void AddMoveTo(const glm::vec3& newPos);
        Drizzle_API void AddLookAt(const glm::vec3& target);
        Drizzle_API void AddSetUp(const glm::vec3& newUp);

        Drizzle_API void SetPerspective(float fovDegrees, float aspect, float nearClip, float farClip);
        Drizzle_API void SetOrthographic(float orthoSize, float aspect, float nearClip, float farClip);

        Drizzle_API void SetFov(float fovDegrees);
        Drizzle_API void SetAspectRatio(float aspect);
        Drizzle_API void SetNearClip(float nearClip);
        Drizzle_API void SetFarClip(float farClip);
        Drizzle_API void SetOrthoSize(float size);
        Drizzle_API void SetProjectionType(ProjectionType type);
        Drizzle_API void AddFov(float fovDegrees);
        Drizzle_API void AddAspectRatio(float aspect);
        Drizzle_API void AddNearClip(float nearClip);
        Drizzle_API void AddFarClip(float farClip);
        Drizzle_API void AddOrthoSize(float size);
    private:
        glm::mat4* Matrix;
    };
}