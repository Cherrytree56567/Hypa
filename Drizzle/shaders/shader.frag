#version 450

struct Light {
    vec3 position;
    float intensity;
    vec3 color;
    float radius;
    vec3 direction;
    float innerAngle;
    float outerAngle;
    int lightType;
    vec2 padding;
};


layout (location = 0) in vec3 inColor;
layout (location = 1) in vec2 inUV;
layout (location = 0) out vec4 outFragColor;

layout(set = 0, binding = 0) uniform sampler2D displayTexture;

layout(std140, binding = 0) uniform LightBuffer {
    Light lights[128];
};

void main() {
	outFragColor = texture(displayTexture, inUV);
}
