#version 400

layout (location = 0) in vec3 vertexPosition;   //позиция вершины
layout (location = 1) in vec3 vertexNormal;     //нормаль вершины
layout (location = 2) in vec2 vertexTexCoord;   //текст. коорд. вершины

out vec3 eyeVertPos;
out vec3 eyeNormal;
out vec3 eyeLightPos;

uniform mat3 NormalMatrix;
uniform mat4 MVPMatrix;         // Proj * View * Model
uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform vec3 lightPosition;     //позиция источника света

void main() {
        // Получаем вектор нормали в сис-ме коорд. наблюдателя (eye)
        eyeNormal = normalize(NormalMatrix * vertexNormal);
        // Получаем позицию вершины в eye
        eyeVertPos = ModelViewMatrix * vec4(vertexPosition, 1.0);

        eyeLightPos = vec3(ViewMatrix * vec4(lightPosition, 1.0));



        gl_Position = MVPMatrix * vec4(vertexPosition, 1.0);
}
