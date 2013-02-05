#version 400

in vec3 color;
in vec2 texCoord;

layout (location = 0) out vec4 FragColor;

void main(void) {
        const float scale = 100.0;
        bvec2 toDiscard = greaterThan(fract(texCoord * scale), vec2(0.5,0.5));
        if(all(toDiscard)) discard;

        FragColor = vec4(color, 1.0);
}
