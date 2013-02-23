#version 400

in vec4 vPosition;
in vec3 vNormal;
in vec2 texCoord;

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

uniform Material material;
uniform Light light;
uniform mat4 V;
uniform sampler2D inputTexture;
uniform float textureWidth;
uniform float textureHeight;

subroutine vec4 RenderPassType();
subroutine uniform RenderPassType renderPass;

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

/** Возвращает значение яркости цвета
  */
float luma(vec3 color) {
        return 0.2126*color.r + 0.7152*color.g + 0.0722*color.b;
}

subroutine (RenderPassType)
vec4 phongLighting() {
        return vec4(phongModel(vec3(vPosition), vNormal),1.0);
}

subroutine (RenderPassType)
vec4 sobelOperator() {
        float dx = 1.0/float(textureWidth);
        float dy = 1.0/float(textureHeight);

        float a11 = luma(texture2D(inputTexture, texCoord+vec2(-dx,dy)).rgb);
        float a12 = luma(texture2D(inputTexture, texCoord+vec2(0,dy)).rgb);
        float a13 = luma(texture2D(inputTexture, texCoord+vec2(dx,dy)).rgb);

        float a21 = luma(texture2D(inputTexture, texCoord+vec2(-dx,0)).rgb);
        float a23 = luma(texture2D(inputTexture, texCoord+vec2(dx,0)).rgb);

        float a31 = luma(texture2D(inputTexture, texCoord+vec2(-dx,-dy)).rgb);
        float a32 = luma(texture2D(inputTexture, texCoord+vec2(0,-dy)).rgb);
        float a33 = luma(texture2D(inputTexture, texCoord+vec2(dx,-dy)).rgb);

        float Gx = -a11 - 2*a12 - a13 + a31 + 2*a32 + a33;
        float Gy = -a11 - 2*a21 - a32 + a13 + 2*a23 + a33;

        vec3 color =  vec3(sqrt(Gx*Gx + Gy*Gy));
        return vec4(color,1.0);
}

subroutine (RenderPassType)
vec4 identityOperator() {
        return texture2D(inputTexture, texCoord);
}

void main() {
        FragColor = renderPass();
}
