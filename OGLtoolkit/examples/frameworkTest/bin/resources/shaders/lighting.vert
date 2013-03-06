#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;

out vec4 vPosition;
out vec3 vNormal;
out vec2 texCoord;

uniform mat4 MV;        //из model в view
uniform mat4 MVP;       //из model в экранные координаты
uniform mat3 N;         //нормаль из model во view

void main() {
        vec4 pos = vec4(vertexPosition, 1.0);
        vPosition = MV * pos;
        vNormal = normalize(N * vertexNormal);
        texCoord = vertexTexCoord;

        gl_Position = MVP * pos;
}
