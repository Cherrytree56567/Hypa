#version 330 core

in vec3 TexCoords;
in vec3 Normals;

out vec4 FragColor;

in float AAColor;

vec3 rainbow(float value) {
    float r = abs(sin(value * 6.28318 + 0.0)); // Red channel
    float g = abs(sin(value * 6.28318 + 2.09439)); // Green channel
    float b = abs(sin(value * 6.28318 + 4.18879)); // Blue channel
    return vec3(r, g, b);
}

void main() {
    vec3 color = rainbow(AAColor);
    FragColor = vec4(color, 1.0);
}
