#version 400

in vec3 position;
in vec3 normal;
layout (location = 0) out vec4 FragColor;

struct SpotLight {
        vec3    wPosition;      //позиция
        vec3    wTarget;        //направление луча
        float   cutoff;         //угол развертки конуса
        float   pow;            //степень изменения освещенности на концах

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
uniform SpotLight spot;
uniform mat4 V;

vec3 spotShading(vec3 vPos, vec3 vNorm) {
        vec3 vPosition = vec3(V * vec4(spot.wPosition,1.0));
        vec3 vTarget = vec3(V * vec4(spot.wTarget, 1.0));
        vec3 vDirection = normalize(vTarget - vPosition);

        vec3 s = normalize(vPosition - vPos);              //положение источника света
        float angle = acos(dot(-s, vDirection));           //угол между -s и direction в радианах
        float cutoff = radians(clamp(spot.cutoff, 0, 90));

        vec3 ambient = spot.ambient * material.ambient;
        vec3 diffuse = spot.diffuse * material.diffuse * max(dot(vNorm, s), 0.0);
        if (angle < cutoff) {                                   //внутри конуса
                float intensity = clamp(pow(dot(-s, vDirection), spot.pow), 0.05, 1.0);      //интенсивность пропорциональна углу

                vec3 v = normalize(-vPos);
                vec3 h = normalize(v+s);

                vec3 specular = spot.specular * material.specular * pow(max(dot(h,vNorm), 0.0), material.shininess);
                return intensity * (ambient+diffuse+specular);
        } else {                                                //вне конуса
                return 0.05*(ambient+diffuse);
        }
}

vec3 stepShading() {
        const int level = 3;
        vec3 color = spotShading(position, normal);
        return floor(color*level)/level;
}

void main(void) {
        FragColor = vec4(stepShading(), 1.0);
}
