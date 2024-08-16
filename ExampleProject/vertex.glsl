#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoords;
layout (location = 2) in vec3 aNormals;

out vec3 TexCoords;
out vec3 Normals;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
   TexCoords = aTexCoords;
   Normals = aNormals;
}