#version 400
in vec3 wViewDir;
in vec3 wNormal;
layout (location = 0) out vec4 FragColor;

struct MaterialInfo {
        vec3    baseColor;
        float   diffuseFactor;
        float   specularFactor;
};

uniform samplerCube base;
uniform samplerCube diffusemap;
uniform samplerCube specularmap;
uniform MaterialInfo material;

void main(void) {
        vec3 r = reflect(-wViewDir, wNormal);

        vec4 diffuseColor = textureCube(diffusemap, wNormal);
        vec4 specularColor = textureCube(specularmap, r);

        vec3 color = mix(material.baseColor, material.baseColor*diffuseColor, material.diffuseFactor);
        color += specularColor*material.specularFactor;

        FragColor = vec4(color, 1.0);
}
