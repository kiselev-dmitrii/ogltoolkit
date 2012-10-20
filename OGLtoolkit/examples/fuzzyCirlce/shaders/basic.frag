#version 400

in vec2 texCoord;

layout (location = 0) out vec4 FragColor;

uniform BlobSettings {
        vec4    innerColor;
        vec4    outerColor;
        float   innerRadius;
        float   outerRadius;
};

void main() {
        float dx = 0.5 - texCoord.x;
        float dy = 0.5 - texCoord.y;
        float distance = sqrt(dx*dx + dy*dy);
        FragColor = mix(innerColor, outerColor, smoothstep(innerRadius, outerRadius, distance));
}
