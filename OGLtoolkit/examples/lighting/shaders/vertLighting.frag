#version 400

in vec3 frontColor;
in vec3 backColor;

layout (location = 0) out vec4 FragColor;

void main(void) {
        if(gl_FrontFacing)  FragColor = vec4(frontColor, 1.0);
        else FragColor = vec4(backColor, 1.0);
}
