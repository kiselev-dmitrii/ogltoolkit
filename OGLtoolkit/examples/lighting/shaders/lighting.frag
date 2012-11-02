#version 400

in vec3 eyeLightPos;
in vec3 eyeVertPos;
in vec3 eyeNormal;

uniform vec3 Kd;                //коэфф. отражаемости для предмета
uniform vec3 Ld;                //интенсивность источника света
uniform vec3 Ka;
uniform vec3 La;
uniform vec3 Ks;
uniform vec3 Ls;

layout (location = 0) out vec4 FragColor;

void main() {
        // Получаем орту направленную из верш на источник света
        vec3 lightVector = normalize(eyeLightPos - vec3(eyeVertPos));
        // Орта направленная на наблюдателя
        vec3 viewVector = normalize(-vec3(eyeVertPos));
        //Цвет
        vec3 ambientColor = Ka*La;
        vec3 diffuseColor = Kd * Ld * max(dot(lightVector, eyeNormal), 0.0);
        vec3 specularColor = Ks * Ls * max(pow(dot(viewVector, reflect(-lightVector, eyeNormal)),80), 0.0);

        FragColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
}
