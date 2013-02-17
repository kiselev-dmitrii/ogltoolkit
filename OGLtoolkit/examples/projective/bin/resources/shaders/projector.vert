#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out vec4 vPosition;
out vec3 vNormal;
out vec4 projTexCoord;

uniform mat4 ProjectorMatrix;   //из world в экранные координаты проектора
uniform vec3 wCameraPosition;

uniform mat4 MV;        //из model в view
uniform mat4 M;         //из model в world
uniform mat4 MVP;       //из model в экранные координаты
uniform mat3 N;         //нормаль из model во view

void main() {
        vec4 pos = vec4(vertexPosition, 1.0);

        vPosition = MV * pos;
        vNormal = normalize(N * vertexNormal);
        projTexCoord = ProjectorMatrix * M * pos;

        gl_Position = MVP * pos;
}
