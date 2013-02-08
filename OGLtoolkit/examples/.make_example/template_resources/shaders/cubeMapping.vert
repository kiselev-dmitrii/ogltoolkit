#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out vec3 reflectDir;
out vec3 refractDir;
out float reflectAbility;

struct MaterialInfo {
        float   ratio;
        float   reflectionFactor;
};

uniform MaterialInfo    material;
uniform bool            isDrawSkybox;
uniform vec3            wCameraPosition;

uniform mat4 M;         //из model в world
uniform mat4 MVP;       //из model в экранные координаты

void main() {
        vec3 wPosition = vec3(M * vec4(vertexPosition, 1.0));

        if(isDrawSkybox) {
                reflectDir = wPosition;
        } else {
                vec3 wNormal = vec3(M * vec4(vertexNormal, 0.0));
                vec3 wViewDir = normalize(wCameraPosition - wPosition);

                refractDir = refract(-wViewDir, wNormal, material.ratio);
                reflectDir = reflect(-wViewDir, wNormal);

                float fallAngle = acos(dot(wViewDir, wNormal));
                float refractAngle = acos(dot(refractDir, -wNormal));
                reflectAbility = pow(tan(fallAngle-refractAngle)/tan(fallAngle+refractAngle),2);
        }

        gl_Position = MVP * vec4(vertexPosition, 1.0);
}
