#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;

out vec3 frontColor;
out vec3 backColor;

struct Light {
        vec3    wPosition;
        vec3    ambient;
        vec3    diffuse;
        vec3    specular;
};

struct Material {
        vec3    ambient;
        vec3    diffuse;
        vec3    specular;
        float   shininess;
};

uniform Material material;
uniform Light light;

uniform mat4 V;         //из world в view
uniform mat4 MV;        //из model в view
uniform mat4 MVP;       //из model в экранные координаты
uniform mat3 N;         //нормаль из model во view

/** Объявляем прототип подпрограммы (что-то вроде указателя на функцию)
  * На деле, это тип
  */
subroutine vec3 Shading(vec3 vPos, vec3 vNorm);

//конкретный uniform-указатель, который будет передавтаться из вне
subroutine uniform Shading frontShading;
subroutine uniform Shading backShading;

/** Реализует затенение по Фонгу. Сигнатура функции должна быть как у Shading
  */
subroutine (Shading)                                    //говорим, что это может быть значением для типа Shading
vec3 phongShading(vec3 vPos, vec3 vNorm) {
        vec3 vLightPos = vec3(V * vec4(light.wPosition, 1.0));
        vec3 s = normalize(vLightPos - vPos);
        vec3 r = reflect(-s, vNorm);
        vec3 v = normalize(-vPos);
        float nDotS = max(dot(vNorm, s), 0.0);

        vec3 ambient = light.ambient * material.ambient;
        vec3 diffuse = light.diffuse * material.diffuse * nDotS;
        vec3 specular = light.specular * material.specular * pow(max(dot(v, r), 0.0), material.shininess);

        return ambient+diffuse+specular;
}

/** Реализует обычное диффузное затенение
  */
subroutine (Shading)
vec3 diffuseShading(vec3 vPos, vec3 vNorm) {
        vec3 vLightPos = vec3(V * vec4(light.wPosition, 1.0));
        vec3 s = normalize(vLightPos - vPos);
        return light.diffuse * material.diffuse * max(dot(vNorm, s), 0.0);
}

void main() {
        /** Вектора с префиксом v,m,w означают вектора
          * в видовой, модельной и мировой сис-ме координат
          */

        // Переводим вектора в видовую сис-му
        vec3 vPos = vec3(MV * vec4(vertexPosition, 1.0));
        vec3 vNorm = normalize(N * vertexNormal);

        frontColor = frontShading(vPos, vNorm);
        backColor = backShading(vPos, -vNorm);

        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
