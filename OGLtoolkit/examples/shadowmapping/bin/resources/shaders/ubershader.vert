#version 400

layout (location = 0) in vec3 _vertexPosition;
layout (location = 1) in vec3 _vertexNormal;
layout (location = 2) in vec2 _vertexTexCoord;

out vec4 vPosition;
out vec3 vNormal;
out vec2 texCoord;

#ifndef DRAW_QUAD
uniform mat4 _MV;        //из model в view
uniform mat4 _MVP;       //из model в экранные координаты
uniform mat3 _N;         //нормаль из model во view
#endif DRAW_QUAD

void main() {
        vec4 pos = vec4(_vertexPosition, 1.0);

        #ifdef DRAW_QUAD
        vPosition = pos;
        vNormal = _vertexNormal;
        texCoord = _vertexTexCoord;

        gl_Position = pos;
        #else
        vPosition = _MV * pos;
        vNormal = normalize(_N * _vertexNormal);
        texCoord = _vertexTexCoord;

        gl_Position = _MVP * pos;
        #endif
}
