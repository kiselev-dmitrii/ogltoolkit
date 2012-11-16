#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;
layout (location = 3) in vec3 vertexTangent;

out vec3 tLightDir;
out vec3 tViewDir;
out vec2 texCoord;

struct Light {
        vec3    wPosition;
        vec3    intensity;
};

uniform Light light;

uniform mat4 V;         //из world во view
uniform mat4 MV;        //из model в view
uniform mat4 MVP;       //из model в экранные координаты
uniform mat3 N;         //нормаль из model во view

void main() {
        // Переводим тангент и нормаль из model во view и вычисляем бинормаль
        vec3 vNormal = normalize(N * vertexNormal);
        vec3 vTangent = normalize(N * vertexTangent);
        vec3 vBinormal = cross(vNormal, vTangent);

        // Получаем матрицу перехода из view в tangent
        mat3 ViewToTangent = mat3( vTangent.x, vBinormal.x, vNormal.x,
                                   vTangent.y, vBinormal.y, vNormal.y,
                                   vTangent.z, vBinormal.z, vNormal.z );

        // Получаем координаты вершины и ист. света во view
        vec3 vVertexPosition = vec3(MV * vec4(vertexPosition, 1.0));
        vec3 vLightPosition = vec3(V * vec4(light.wPosition, 1.0));

        // Передаем во фрагментный шейдер направление света и направление взгляда
        tLightDir = ViewToTangent * normalize(vLightPosition-vVertexPosition);
        tViewDir = ViewToTangent * normalize(-vVertexPosition);
        texCoord = vertexTexCoord;

        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
