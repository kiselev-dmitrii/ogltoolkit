#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;

out vec3 position;
out vec3 normal;
out vec2 texCoord;

uniform mat4 MV;        //из model в view
uniform mat4 MVP;       //из model в экранные координаты
uniform mat3 N;         //нормаль из model во view

void main() {
        /** Вычисляем позицию и нормаль во view*/
        position = vec3(MV * vec4(vertexPosition, 1.0));
        normal = normalize(N * vertexNormal);
        texCoord = vertexTexCoord;

        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
