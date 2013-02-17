#version 400

in vec4 vPosition;
in vec3 vNormal;
in vec4 projTexCoord;

layout (location = 0) out vec4 FragColor;

struct Light {
        vec3    position;
        vec3    color;
};

struct Material {
        vec3    ambient;
        vec3    diffuse;
        vec3    specular;
        float   shininess;
};

uniform sampler2D projectorTexture;
uniform Material material;
uniform Light light;
uniform mat4 V;

vec3 phongModel(vec3 pos, vec3 norm) {
        vec3 vLightPos = vec3(V * vec4(light.position,1.0));

        vec3 s = normalize(vLightPos - pos);
        vec3 v = normalize(-pos.xyz);
        vec3 r = reflect(-s, norm);

        vec3 ambient = light.color * material.ambient;

        float sDotN = max(dot(s,norm), 0.0);
        vec3 diffuse = light.color * material.diffuse * sDotN;

        vec3 specular = vec3(0.0);
        if (sDotN > 0.0) {
                specular = light.color * material.specular * pow(max(dot(r,v), 0.0), material.shininess);
        }

        return ambient + diffuse + specular;
}

void main() {
        vec3 color = phongModel(vec3(vPosition), vNormal);

        vec4 textureColor = vec4(0.0);
        if (projTexCoord.z > 0.0) {
                textureColor = texture2DProj(projectorTexture, projTexCoord);
        }

        FragColor = vec4(color, 1.0)*0.5 + textureColor*0.5;
}
