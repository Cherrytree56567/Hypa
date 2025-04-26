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

layout (location = 0) in vec3  inColor;
layout (location = 1) in vec2  inUV;
layout (location = 2) in vec3  inNormal;
layout (location = 3) in vec3  world_pos;
layout (location = 4) flat in int  isSky;
layout (location = 5) in float metalness;
layout (location = 6) in float roughness;  // now used
layout (location = 7) in mat4  viewMat;
layout (location = 0) out vec4  outFragColor;

layout(set = 0, binding = 0) uniform sampler2D displayTexture;
layout(set = 0, binding = 1) uniform sampler2D ambientTex;
layout(set = 0, binding = 2, std140) uniform LightBuffer {
    Light lights[128];
};

const int MAX_LIGHTS = 128;
const float PI = 3.14159265359;

// GGX / Trowbridge‐Reitz normal distribution
float DistributionGGX(vec3 N, vec3 H, float rough) {
    float a      = rough*rough;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    return a2 / (PI * denom * denom);
}

// Smith’s method to combine geometry for both light & view
float GeometrySmith(vec3 N, vec3 V, vec3 L, float rough) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, rough);
    float ggx1  = GeometrySchlickGGX(NdotL, rough);
    return ggx1 * ggx2;
}

void main() {
    vec4 baseColor    = texture(displayTexture, inUV);
    vec3  finalColor  = vec3(0.0);
    vec3 N = normalize(inNormal);
    vec3 cameraViewPos = viewMat[3].xyz;
    vec3 VV = normalize(cameraViewPos - world_pos);
    vec3 RR = reflect(-VV, N);

    // remap R.xy from [−1,1]→[0,1]
    vec2 uvMatcap = RR.xy * 0.5 + 0.5;
    vec3 ambientLight = texture(ambientTex, uvMatcap).rgb * 0.2;

    if (isSky == 1) {
        outFragColor = baseColor;
        return;
    }

    vec3 V = normalize((inverse(viewMat) * vec4(0,0,0,1)).xyz - world_pos);

    // F0 for non‐metals is usually ~4%, metals use baseColor
    const vec3 F0_dielectric = vec3(0.04);

    for (int i = 0; i < MAX_LIGHTS; ++i) {
        Light L = lights[i];
        if (L.intensity <= 0.0) continue;

        // --- compute light direction & attenuation (same as before) ---
        vec3 lightDir;
        float attenuation = 1.0;
        if (L.lightType == 0) {            // point
            vec3 toL = L.position - world_pos;
            float dist = length(toL);
            if (L.radius <= 0.0) continue;
            attenuation = 1.0 / (1.0 + 0.1*dist + 0.01*dist*dist);
            lightDir = normalize(toL);

        } else if (L.lightType == 1) {     // directional
            lightDir = normalize(-L.direction);

        } else if (L.lightType == 2) {     // spot
            vec3 toL   = L.position - world_pos;
            float dist = length(toL);
            if (dist > L.radius) continue;
            float angle = acos(dot(normalize(L.direction), normalize(-toL)));
            if (angle > L.outerAngle) continue;
            float spot = smoothstep(L.outerAngle, L.innerAngle, angle);
            attenuation = (1.0 - dist/L.radius) * spot;
            lightDir = normalize(toL);

        } else if (L.lightType == 3) {     // area
            vec3 toL   = L.position - world_pos;
            float dist = length(toL);
            if (dist > L.radius) continue;
            attenuation = smoothstep(L.radius, 0.0, dist);
            lightDir = normalize(toL);

        } else continue;

        float NdotL = max(dot(N, lightDir), 0.0);
        if (NdotL <= 0.0) continue;

        // --- PBR BRDF terms ---
        vec3 H = normalize(lightDir + V);
        // Fresnel
        vec3 F0 = mix(F0_dielectric, baseColor.rgb, metalness);
        float VdotH = max(dot(V, H), 0.0);
        vec3  F     = F0 + (1.0 - F0) * pow(1.0 - VdotH, 5.0);

        // Normal distribution
        float D = DistributionGGX(N, H, roughness);
        // Geometry
        float G = GeometrySmith(N, V, lightDir, roughness);

        // Specular term
        float denom = 4.0 * max(dot(N, V), 0.0) * NdotL + 0.001;
        vec3 specular = (D * G * F) / denom;

        // Diffuse term (energy‐conserving Lambertian)
        vec3 kD = (1.0 - F) * (1.0 - metalness);
        vec3 diffuse = kD * baseColor.rgb / PI;

        // accumulate
        finalColor += (diffuse + specular) * L.color * L.intensity * attenuation * NdotL;
    }

    // add ambient
    finalColor = finalColor + ambientLight * (1.0 - metalness);

    outFragColor = vec4(finalColor, baseColor.a);
}
