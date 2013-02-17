#version 400

in vec3 reflectDir;
in vec3 refractDir;
in float reflectAbility;
layout (location = 0) out vec4 FragColor;

struct MaterialInfo {
        float   ratio;
        float   reflectFactor;
};

uniform samplerCube cubemap;
uniform bool isDrawSkybox;
uniform MaterialInfo material;

void main(void) {
        vec4 reflectColor = textureCube(cubemap, reflectDir);
        vec4 refractColor = textureCube(cubemap, refractDir);

        if(isDrawSkybox) {
                FragColor = reflectColor;
        } else {
                FragColor = mix(refractColor, reflectColor, material.reflectFactor*reflectAbility);
        }

}
