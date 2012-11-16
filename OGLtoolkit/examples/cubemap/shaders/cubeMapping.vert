#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out vec3 wReflectDir;

uniform bool isDrawSkybox;
uniform vec3 wCameraPosition;

uniform mat4 M;         //из model в world
uniform mat4 MVP;       //из model в экранные координаты

void main() {
        vec3 wPosition = vec3(M * vec4(vertexPosition, 1.0));

        if(isDrawSkybox) {
                wReflectDir = wPosition;
        } else {
                vec3 wNormal = vec3(M * vec4(vertexNormal, 1.0));
                vec3 wViewDir = normalize(wCameraPosition - wPosition);

                wReflectDir = reflect(-wViewDir, wNormal);
        }

        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
