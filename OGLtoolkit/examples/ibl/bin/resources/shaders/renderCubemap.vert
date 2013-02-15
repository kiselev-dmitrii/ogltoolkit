#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out vec3 dir;

uniform mat4 MVP;       //из model в экранные координаты

void main() {
        dir = vertexPosition;
        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
