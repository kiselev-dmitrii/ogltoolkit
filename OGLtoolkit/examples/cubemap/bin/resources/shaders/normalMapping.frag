#version 400

in vec3 tLightDir;
in vec3 tViewDir;
in vec2 texCoord;
layout (location = 0) out vec4 FragColor;

struct Light {
        vec3    wPosition;
        vec3    color;          //общий цвет источника
};

struct Material {
        vec3    ambient;
        vec3    specular;
        float   shininess;
};

uniform Material material;
uniform Light light;
uniform sampler2D baseSampler;
uniform sampler2D normalSampler;

vec3 phongShading(vec3 normal, vec3 textureColor) {
        vec3 r = reflect(-tLightDir, normal);

        vec3 ambient = light.color * material.ambient;
        float nDotS = max(dot(normal, tLightDir), 0.0);
        vec3 diffuse =  light.color * textureColor * nDotS;     //нет диффузного цвета, т.к теперь это текстура

        vec3 specular = vec3(0.0);
        if (nDotS > 0) {
                specular = light.color * material.specular * pow(max(dot(tViewDir, normal), 0.0), material.shininess);
        }
        return ambient + diffuse + specular;
}



void main(void) {
        vec3 textureColor = texture2D(baseSampler, texCoord).xyz;
        vec3 normal = texture2D(normalSampler, texCoord).xyz*2.0 - 1.0;

        FragColor = vec4(phongShading(normal, textureColor), 1.0);
}
