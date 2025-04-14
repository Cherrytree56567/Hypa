#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <string>

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
        Lighting(std::string nam, LightType type, glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f) : type(type), color(color), intensity(intensity), name(nam) {}

        virtual ~Lighting() {}

        LightType getType() const { return type; }
        glm::vec3 getColor() const { return color; }
        float getIntensity() const { return intensity; }

		void setColor(const glm::vec3& newColor) { color = newColor; }
		void setIntensity(float newIntensity) { intensity = newIntensity; }

        virtual Light GetLight() const { return Light(); }
		std::string getName() const { return name; }

		void hideLight(bool hid) { hide = hid; }
		bool isHidden() const { return hide; }

    protected:
        LightType type;
        glm::vec3 color;
        float intensity;
        std::string name;
		bool hide = false;
    };

    class PointLight : public Lighting {
    public:
        PointLight(std::string name, glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float radius = 10.0f) 
            : Lighting(name, LightType::Point, color, intensity), position(position), radius(radius) {}

        glm::vec3 getPosition() const { return position; }
        float getRadius() const { return radius; }

		void setPosition(const glm::vec3& newPosition) { position = newPosition; }
		void setRadius(float newRadius) { radius = newRadius; }

        Light GetLight() const override;

    private:
        glm::vec3 position;
        float radius;
    };

    class DirectionalLight : public Lighting {
    public:
        DirectionalLight(std::string name, glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f) 
            : Lighting(name, LightType::Directional, color, intensity), direction(direction) {}

        glm::vec3 getDirection() const { return direction; }
		void setDirection(const glm::vec3& newDirection) { direction = newDirection; }

        Light GetLight() const override;
    private:
        glm::vec3 direction;
    };

    class SpotLight : public Lighting {
    public:
        SpotLight(std::string name, glm::vec3 position = glm::vec3(0.0f), glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float innerAngle = glm::radians(12.5f), float outerAngle = glm::radians(17.5f))
            : Lighting(name, LightType::Spot, color, intensity), position(position), direction(direction), innerAngle(innerAngle), outerAngle(outerAngle) {}

        glm::vec3 getPosition() const { return position; }
        glm::vec3 getDirection() const { return direction; }
        float getInnerAngle() const { return innerAngle; }
        float getOuterAngle() const { return outerAngle; }
		void setPosition(const glm::vec3& newPosition) { position = newPosition; }
		void setDirection(const glm::vec3& newDirection) { direction = newDirection; }
		void setInnerAngle(float newInnerAngle) { innerAngle = newInnerAngle; }
		void setOuterAngle(float newOuterAngle) { outerAngle = newOuterAngle; }

		Light GetLight() const override;

    private:
        glm::vec3 position;
        glm::vec3 direction;
        float innerAngle;
        float outerAngle;
    };

    class AreaLight : public Lighting {
    public:
        AreaLight(std::string name, glm::vec3 position = glm::vec3(0.0f), glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, glm::vec2 size = glm::vec2(1.0f, 1.0f))
            : Lighting(name, LightType::Area, color, intensity), position(position), direction(direction), size(size) {}

        glm::vec3 getPosition() const { return position; }
        glm::vec3 getDirection() const { return direction; }
        glm::vec2 getSize() const { return size; }
		void setPosition(const glm::vec3& newPosition) { position = newPosition; }
		void setDirection(const glm::vec3& newDirection) { direction = newDirection; }
		void setSize(const glm::vec2& newSize) { size = newSize; }

		Light GetLight() const override;

    private:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec2 size;
    };
}