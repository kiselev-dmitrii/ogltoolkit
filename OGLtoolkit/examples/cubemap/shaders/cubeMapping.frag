#version 400

in vec3 wReflectDir;
layout (location = 0) out vec4 FragColor;

struct MirrorSettings {
        float   reflectFactor;
        vec3    baseColor;
};

uniform samplerCube cubemap;
uniform bool isDrawSkybox;
uniform MirrorSettings mirror;

void main(void) {
        vec4 cubemapColor = textureCube(cubemap, wReflectDir);

        if(isDrawSkybox) {
                FragColor = cubemapColor;
        } else {
                FragColor = mix(vec4(mirror.baseColor,1.0), cubemapColor, mirror.reflectFactor);
        }

}
