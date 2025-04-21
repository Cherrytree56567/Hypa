#include "Camera.h"

namespace Drizzle {
    Camera::Camera(glm::mat4 viewMat, glm::mat4 projMat) {
        projectionMatrix = projMat;
        viewMatrix = viewMat;
    }

    void Camera::MoveTo(const glm::vec3& newPos) {
        viewMatrix = glm::translate(viewMatrix, newPos);
    }

    void Camera::LookAt(const glm::vec3& target) {
        glm::vec3 eye = glm::vec3(glm::inverse(viewMatrix)[3]);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        viewMatrix = glm::lookAt(eye, target, up);
    }

    void Camera::SetUp(const glm::vec3& newUp) {
        glm::vec3 eye = glm::vec3(glm::inverse(viewMatrix)[3]);
        glm::vec3 target = eye - glm::vec3(viewMatrix[2]);
        viewMatrix = glm::lookAt(eye, target, newUp);
    }

    void Camera::AddMoveTo(const glm::vec3& offset) {
        viewMatrix = glm::translate(viewMatrix, offset);
    }

    void Camera::AddLookAt(const glm::vec3& offset) {
        glm::vec3 eye = glm::vec3(glm::inverse(viewMatrix)[3]);
        glm::vec3 currentForward = -glm::vec3(viewMatrix[2]);
        glm::vec3 newTarget = eye + currentForward + offset;
        glm::vec3 up = glm::vec3(viewMatrix[1]);
        viewMatrix = glm::lookAt(eye, newTarget, up);
    }

    void Camera::AddSetUp(const glm::vec3& offset) {
        glm::vec3 eye = glm::vec3(glm::inverse(viewMatrix)[3]);
        glm::vec3 target = eye - glm::vec3(viewMatrix[2]);
        glm::vec3 up = glm::vec3(viewMatrix[1]) + offset;
        viewMatrix = glm::lookAt(eye, target, up);
    }

    void Camera::SetPerspective(float fovDeg, float aspectRatio, float nearZ, float farZ) {
        projectionMatrix = glm::perspective(glm::radians(fovDeg), aspectRatio, nearZ, farZ);
    }

    void Camera::SetOrthographic(float orthoSz, float aspectRatio, float nearZ, float farZ) {
        float halfW = orthoSz * aspectRatio * 0.5f;
        float halfH = orthoSz * 0.5f;
        projectionMatrix = glm::ortho(-halfW, halfW, -halfH, halfH, nearZ, farZ);
    }

    void Camera::SetFov(float f) {
        float aspect = projectionMatrix[0][0];
        SetPerspective(f, aspect, 0.1f, 100.0f);
    }

    void Camera::SetAspectRatio(float a) {
        SetPerspective(45.0f, a, 0.1f, 100.0f);
    }

    void Camera::SetNearClip(float n) {
        SetPerspective(45.0f, 1.0f, n, 100.0f);
    }

    void Camera::SetFarClip(float f) {
        SetPerspective(45.0f, 1.0f, 0.1f, f);
    }

    void Camera::SetOrthoSize(float s) {
        SetOrthographic(s, 1.0f, 0.1f, 100.0f);
    }

    void Camera::AddFov(float f) {
        SetPerspective(45.0f + f, 1.0f, 0.1f, 100.0f);
    }

    void Camera::AddAspectRatio(float a) {
        SetPerspective(45.0f, 1.0f + a, 0.1f, 100.0f);
    }

    void Camera::AddNearClip(float n) {
        SetPerspective(45.0f, 1.0f, 0.1f + n, 100.0f);
    }

    void Camera::AddFarClip(float f) {
        SetPerspective(45.0f, 1.0f, 0.1f, 100.0f + f);
    }

    void Camera::AddOrthoSize(float s) {
        SetOrthographic(1.0f + s, 1.0f, 0.1f, 100.0f);
    }

    void Camera::SetProjectionType(ProjectionType type) {
        if (type == ProjectionType::Perspective) {
            SetPerspective(45.0f, 1.0f, 0.1f, 100.0f);
        }
        else {
            SetOrthographic(1.0f, 1.0f, 0.1f, 100.0f);
        }
    }

    glm::mat4 Camera::GetMatrix() const {
        return projectionMatrix * viewMatrix;
    }

    glm::mat4 Camera::GetViewMatrix() const {
        return viewMatrix;
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return projectionMatrix;
    }
}
