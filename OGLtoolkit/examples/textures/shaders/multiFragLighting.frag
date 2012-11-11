#version 400

in vec3 position;
in vec3 normal;
in vec2 texCoord;
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

uniform Material material;
uniform Light lights[3];
uniform mat4 V;
uniform sampler2D sampler1;

void phongShading(int lightIndex, vec3 vPos, vec3 vNorm, out vec3 ambAndDiff, out vec3 spec) {
        vec3 vLightPos = vec3(V * vec4(lights[lightIndex].wPosition, 1.0));
        vec3 s = normalize(vLightPos - vPos);
        vec3 v = normalize(-vPos);
        vec3 h = normalize(v+s);
        float nDotS = max(dot(vNorm, s), 0.0);

        vec3 ambient = lights[lightIndex].ambient * material.ambient;
        vec3 diffuse = lights[lightIndex].diffuse * material.diffuse * nDotS;
        vec3 specular = lights[lightIndex].specular * material.specular * pow(max(dot(h, vNorm), 0.0), material.shininess);

        ambAndDiff = ambient + diffuse;
        spec = specular;
}



void main(void) {
        vec3 ambDiff = vec3(0.0);
        vec3 specular = vec3(0.0);
        for(int i=0; i<3; ++i) {
                vec3 tmpDiffAmb, tmpSpec;
                phongShading(i, position, normal, tmpDiffAmb, tmpSpec);
                ambDiff += tmpDiffAmb;
                specular += tmpSpec;
        }

        vec3 color = ambDiff*texture2D(sampler1, texCoord) + specular;

        FragColor = vec4(color, 1.0);
}
