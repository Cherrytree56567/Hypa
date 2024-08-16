#version 330 core

in vec3 TexCoords;
in vec3 Normals;

out vec4 FragColor;

void main() {
   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);
}