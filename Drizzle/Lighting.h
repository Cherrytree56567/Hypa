#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <string>
#include "base.h"

namespace Drizzle {
    struct alignas(16) Light {
        glm::vec3 position;
        float intensity;
        glm::vec3 color;
        float radius;
        glm::vec3 direction;
        float innerAngle;
        float outerAngle;
        int lightType;
    };

    enum class LightType {
        Point,
        Directional,
        Spot,
        Area
    };

    class Lighting {
    public:
        Drizzle_API Lighting(std::string nam, LightType type, glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f) : type(type), color(color), intensity(intensity), name(nam) {}

        Drizzle_API virtual ~Lighting() {}

        Drizzle_API LightType getType() const { return type; }
        Drizzle_API glm::vec3 getColor() const { return color; }
        Drizzle_API float getIntensity() const { return intensity; }

        Drizzle_API void setColor(const glm::vec3& newColor) { color = newColor; }
        Drizzle_API void setIntensity(float newIntensity) { intensity = newIntensity; }

        Drizzle_API virtual Light GetLight() const { return Light(); }
        Drizzle_API std::string getName() const { return name; }

        Drizzle_API void hideLight(bool hid) { hide = hid; }
        Drizzle_API bool isHidden() const { return hide; }

    protected:
        LightType type;
        glm::vec3 color;
        float intensity;
        std::string name;
		bool hide = false;
    };

    class PointLight : public Lighting {
    public:
        Drizzle_API PointLight(std::string name, glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float radius = 10.0f)
            : Lighting(name, LightType::Point, color, intensity), position(position), radius(radius) {}

        Drizzle_API glm::vec3 getPosition() const { return position; }
        Drizzle_API float getRadius() const { return radius; }

        Drizzle_API void setPosition(const glm::vec3& newPosition) { position = newPosition; }
        Drizzle_API void setRadius(float newRadius) { radius = newRadius; }

        Drizzle_API Light GetLight() const override;

    private:
        glm::vec3 position;
        float radius;
    };

    class DirectionalLight : public Lighting {
    public:
        Drizzle_API DirectionalLight(std::string name, glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f)
            : Lighting(name, LightType::Directional, color, intensity), direction(direction) {}

        Drizzle_API glm::vec3 getDirection() const { return direction; }
        Drizzle_API void setDirection(const glm::vec3& newDirection) { direction = newDirection; }

        Drizzle_API Light GetLight() const override;
    private:
        glm::vec3 direction;
    };

    class SpotLight : public Lighting {
    public:
        Drizzle_API SpotLight(std::string name, glm::vec3 position = glm::vec3(0.0f), glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float innerAngle = glm::radians(12.5f), float outerAngle = glm::radians(17.5f))
            : Lighting(name, LightType::Spot, color, intensity), position(position), direction(direction), innerAngle(innerAngle), outerAngle(outerAngle) {}

        Drizzle_API glm::vec3 getPosition() const { return position; }
        Drizzle_API glm::vec3 getDirection() const { return direction; }
        Drizzle_API float getInnerAngle() const { return innerAngle; }
        Drizzle_API float getOuterAngle() const { return outerAngle; }
        Drizzle_API void setPosition(const glm::vec3& newPosition) { position = newPosition; }
        Drizzle_API void setDirection(const glm::vec3& newDirection) { direction = newDirection; }
        Drizzle_API void setInnerAngle(float newInnerAngle) { innerAngle = newInnerAngle; }
        Drizzle_API void setOuterAngle(float newOuterAngle) { outerAngle = newOuterAngle; }

        Drizzle_API Light GetLight() const override;

    private:
        glm::vec3 position;
        glm::vec3 direction;
        float innerAngle;
        float outerAngle;
    };

    class AreaLight : public Lighting {
    public:
        Drizzle_API AreaLight(std::string name, glm::vec3 position = glm::vec3(0.0f), glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, glm::vec2 size = glm::vec2(1.0f, 1.0f))
            : Lighting(name, LightType::Area, color, intensity), position(position), direction(direction), size(size) {}

        Drizzle_API glm::vec3 getPosition() const { return position; }
        Drizzle_API glm::vec3 getDirection() const { return direction; }
        Drizzle_API glm::vec2 getSize() const { return size; }
        Drizzle_API void setPosition(const glm::vec3& newPosition) { position = newPosition; }
        Drizzle_API void setDirection(const glm::vec3& newDirection) { direction = newDirection; }
        Drizzle_API void setSize(const glm::vec2& newSize) { size = newSize; }

        Drizzle_API Light GetLight() const override;

    private:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec2 size;
    };
}