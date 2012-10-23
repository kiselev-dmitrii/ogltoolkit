#version 400

layout (location = 0) in vec3 vertexPosition;   //позиция вершины
layout (location = 1) in vec3 vertexNormal;     //нормаль вершины
layout (location = 2) in vec2 vertexTexCoord;   //текст. коорд. вершины

out vec3 diffuseColor;

uniform mat3 NormalMatrix;
uniform mat4 MVPMatrix;         // Proj * View * Model
uniform mat4 ModelViewMatrix;

uniform vec3 lightPosition;     //позиция источника света в координатах наблюдателя
uniform vec3 Kd;                //коэфф. отражаемости для предмета
uniform vec3 Ld;                //интенсивность источника света


void main() {
        // Получаем вектор нормали в сис-ме коорд. наблюдателя (eye)
        vec3 eyeNormal = normalize(NormalMatrix * vertexNormal);
        // Получаем позицию вершины в eye
        vec4 eyeVertPos = ModelViewMatrix * vec4(vertexPosition, 1.0);

        // Получаем орту направленную на источник света
        vec3 lightVector = normalize(lightPosition - vec3(eyeVertPos));

        // Вычисляем диффузный свет
        diffuseColor = Kd * Ld * max(dot(lightVector, eyeNormal), 0.0);

        gl_Position = MVPMatrix * vec4(vertexPosition, 1.0);
}
