#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out vec3 wViewDir;
out vec3 wNormal;

uniform mat4 MVP;       //из model в экранные координаты
uniform mat4 M;
uniform vec3 wCameraPosition;

void main() {
        vec3 wPosition = vec3(M * vec4(vertexPosition, 1.0));

        wViewDir = normalize(wCameraPosition - wPosition);
        wNormal = vec3(M * vec4(vertexNormal, 0.0));
        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
