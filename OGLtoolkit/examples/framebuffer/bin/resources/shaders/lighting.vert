#version 400

layout (location = 0) in vec3 vertexPosition;   //позиция вершины
layout (location = 1) in vec3 vertexNormal;     //нормаль вершины
layout (location = 2) in vec2 vertexTexCoord;   //текст. коорд. вершины

out vec3 eyeVertPos;
out vec3 eyeNormal;
out vec3 eyeLightPos;
out vec2 texCoord;

uniform mat3 N;
uniform mat4 MVP;         // Proj * View * Model
uniform mat4 MV;
uniform mat4 V;
uniform vec3 lightPosition;     //позиция источника света

void main() {
        // Получаем вектор нормали в сис-ме коорд. наблюдателя (eye)
        eyeNormal = normalize(N * vertexNormal);
        // Получаем позицию вершины в eye
        eyeVertPos = MV * vec4(vertexPosition, 1.0);

        eyeLightPos = vec3(V * vec4(lightPosition, 1.0));

        texCoord = vertexTexCoord;

        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
