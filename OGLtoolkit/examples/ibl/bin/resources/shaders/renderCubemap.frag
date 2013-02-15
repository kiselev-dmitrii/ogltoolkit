#version 400

in vec3 dir;
layout (location = 0) out vec4 FragColor;

uniform samplerCube cubemap;

void main(void) {
        FragColor = textureCube(cubemap, dir);
}
