#version 400

layout (location = 0) in vec3 vertexPosition;   //позиция вершины
layout (location = 1) in vec3 vertexNormal;     //нормаль вершины
layout (location = 2) in vec2 vertexTexCoord;   //текст. коорд. вершины

out vec3 vertexColor;

uniform mat3 NormalMatrix;
uniform mat4 MVPMatrix;         // Proj * View * Model
uniform mat4 ModelViewMatrix;

uniform vec3 lightPosition;     //позиция источника света
uniform vec3 Kd;                //коэфф. отражаемости для предмета
uniform vec3 Ld;                //интенсивность источника света
uniform vec3 Ka;
uniform vec3 La;
uniform vec3 Ks;
uniform vec3 Ls;


void main() {
        // Получаем вектор нормали в сис-ме коорд. наблюдателя (eye)
        vec3 eyeNormal = normalize(NormalMatrix * vertexNormal);
        // Получаем позицию вершины в eye
        vec4 eyeVertPos = ModelViewMatrix * vec4(vertexPosition, 1.0);

        vec3 eyeLightPos = vec3(ModelViewMatrix * vec4(lightPosition, 1.0));

        // Получаем орту направленную из верш на источник света
        vec3 lightVector = normalize(eyeLightPos - vec3(eyeVertPos));
        // Орта направленная на наблюдателя
        vec3 viewVector = normalize(-vec3(eyeVertPos));

        //Цвет
        vec3 ambientColor = Ka*La;
        float sDotN = max(dot(lightVector, eyeNormal), 0.0);
        vec3 diffuseColor = Kd * Ld * sDotN;
        vec3 specularColor = vec3(0.0);
        if (sDotN > 0.0) {
                specularColor = Ks * Ls * max(pow(dot(viewVector, reflect(-lightVector, eyeNormal)),80), 0.0);
        }

        vertexColor = ambientColor + diffuseColor + specularColor;

        gl_Position = MVPMatrix * vec4(vertexPosition, 1.0);
}
