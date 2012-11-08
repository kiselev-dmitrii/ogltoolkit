#version 400

in vec3 position;
in vec3 normal;
layout (location = 0) out vec4 FragColor;

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

struct Fog {
        float   density;
        vec3    color;
};

uniform Material material;
uniform Light lights[3];
uniform Fog fog;
uniform mat4 V;

vec3 phongShading(int lightIndex, vec3 vPos, vec3 vNorm) {
        vec3 vLightPos = vec3(V * vec4(lights[lightIndex].wPosition, 1.0));
        vec3 s = normalize(vLightPos - vPos);
        vec3 v = normalize(-vPos);
        vec3 h = normalize(v+s);
        float nDotS = max(dot(vNorm, s), 0.0);

        vec3 ambient = lights[lightIndex].ambient * material.ambient;
        vec3 diffuse = lights[lightIndex].diffuse * material.diffuse * nDotS;
        vec3 specular = lights[lightIndex].specular * material.specular * pow(max(dot(h, vNorm), 0.0), material.shininess);

        return ambient+diffuse+specular;
}



void main(void) {
        /** Вычисление света от 3-ех источников*/
        vec3 shadeColor = vec3(0.0);
        for (int i=0; i<3; ++i) shadeColor += phongShading(i, position, normal);

        /** Вычисление тумана*/
        float dist = length(position);          //т.к position во view, то это даст расстояние до фрагмента
        float fogFactor = clamp( exp(-pow(fog.density*dist, 2.0)) , 0.0, 1.0);
        vec3 color = mix(fog.color, shadeColor ,fogFactor);

        FragColor = vec4(color, 1.0);
}
