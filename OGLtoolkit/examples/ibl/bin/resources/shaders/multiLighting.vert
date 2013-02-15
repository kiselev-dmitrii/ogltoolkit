#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out vec3 color;

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
uniform Light lights[3];

uniform mat4 V;         //из world в view
uniform mat4 MV;        //из model в view
uniform mat4 MVP;       //из model в экранные координаты
uniform mat3 N;         //нормаль из model во view

vec3 phongShading(int lightIndex, vec3 vPos, vec3 vNorm) {
        vec3 vLightPos = vec3(V * vec4(lights[lightIndex].wPosition, 1.0));
        vec3 s = normalize(vLightPos - vPos);
        vec3 r = reflect(-s, vNorm);
        vec3 v = normalize(-vPos);
        float nDotS = max(dot(vNorm, s), 0.0);

        vec3 ambient = lights[lightIndex].ambient * material.ambient;
        vec3 diffuse = lights[lightIndex].diffuse * material.diffuse * nDotS;
        vec3 specular = lights[lightIndex].specular * material.specular * pow(max(dot(v, r), 0.0), material.shininess);

        return ambient+diffuse+specular;
}

void main() {
        vec3 vPos = vec3(MV * vec4(vertexPosition, 1.0));
        vec3 vNorm = normalize(N * vertexNormal);

        /** Складываем свет от каждого источника*/
        color = vec3(0.0);
        for(int i=0; i<3; ++i) color += phongShading(i, vPos, vNorm);

        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
