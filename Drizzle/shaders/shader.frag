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
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec3 world_pos;
layout (location = 0) out vec4 outFragColor;

layout(set = 0, binding = 0) uniform sampler2D displayTexture;
layout(set = 0, binding = 1, std140) uniform LightBuffer {
    Light lights[128];
};

const int MAX_LIGHTS = 128;

void main() {
	vec4 baseColor = texture(displayTexture, inUV);
    vec3 finalColor = vec3(0.0);

    vec3 fragPos = world_pos;
    vec3 normal = normalize(inNormal);

    for (int i = 0; i < MAX_LIGHTS; ++i) {
        Light light = lights[i];
        if (light.intensity <= 0.0) continue;

        vec3 lightDir;
        float attenuation = 1.0;

        if (light.lightType == 0) { // Point
            vec3 toLight = light.position - fragPos;
            if (light.radius <= 0.0) continue; // avoid divide-by-zero

            float dist = length(toLight);

            attenuation = 1.0 / (1.0 + 0.1 * dist + 0.01 * dist * dist);

            lightDir = normalize(toLight);

        }else if (light.lightType == 1) { // Directional
            lightDir = normalize(-light.direction);

        } else if (light.lightType == 2) { // Spotlight
            vec3 toLight = light.position - fragPos;
            vec3 toFrag = vec3(fragPos.xy - light.position.xy, 0.0);
            float dist = length(toLight);
            if (dist > light.radius) continue;

            vec3 dirToFrag = normalize(toFrag);
            float angle = acos(dot(normalize(light.direction), dirToFrag));

            if (angle > light.outerAngle) continue;

            float spotEffect = smoothstep(light.outerAngle, light.innerAngle, angle);
            attenuation = (1.0 - (dist / light.radius)) * spotEffect;
            lightDir = normalize(toLight);

        } else if (light.lightType == 3) { // Area
            vec3 toLight = light.position - fragPos;
            float dist = length(toLight);
            if (dist > light.radius) continue;

            attenuation = smoothstep(light.radius, 0.0, dist);
            lightDir = normalize(toLight);
        } else {
            continue;
        }

        float NdotL = max(dot(normal, lightDir), 0.0);
        vec3 lightContribution = clamp(light.color, 0.0, 1.0) * light.intensity * attenuation * NdotL;
        finalColor += lightContribution;
        //outFragColor = vec4(vec3(NdotL), 1.0);
    }

    finalColor = baseColor.rgb * finalColor;
    outFragColor = vec4(finalColor, baseColor.a);
}
