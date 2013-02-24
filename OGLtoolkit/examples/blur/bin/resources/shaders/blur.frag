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
uniform sampler2D depthTexture;
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

/** Производит размытие по вертикали
  */
vec4 blurVertical(float sigma) {
        float dx = 1.0/float(textureWidth);
        float dy = 1.0/float(textureHeight);
        float offsets[10] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

        float weights[10];
        float summ = 0;
        for(int i=0; i<10; ++i) {
                weights[i] = exp(-(i*i)/(2.0*sigma*sigma)) * (1.0/(sqrt(2.0*3.1415)*sigma));
                summ += weights[i];
        }

        vec4 result = texture2D(inputTexture, texCoord) * weights[0]/summ;

        //Вверх и низ
        for(int i=1; i<10; ++i) {
                result += texture2D(inputTexture, texCoord + vec2(0.0,dy)*offsets[i]) * weights[i]/(2.0*summ);
                result += texture2D(inputTexture, texCoord + vec2(0.0,-dy)*offsets[i]) * weights[i]/(2.0*summ);
        }

        return result;

}

/** Производит размытие по горизонтали
  */
vec4 blurHorizontal(float sigma) {
        float dx = 1.0/float(textureWidth);
        float dy = 1.0/float(textureHeight);
        float offsets[10] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

        float weights[10];
        float summ = 0;
        for(int i=0; i<10; ++i) {
                weights[i] = exp(-(i*i)/(2.0*sigma*sigma)) * (1.0/(sqrt(2.0*3.1415)*sigma));
                summ += weights[i];
        }

        vec4 result = texture2D(inputTexture, texCoord) * weights[0]/summ;

        //Вверх и низ
        for(int i=1; i<10; ++i) {
                result += texture2D(inputTexture, texCoord + vec2(dx,0.0)*offsets[i]) * weights[i]/(2.0*summ);
                result += texture2D(inputTexture, texCoord + vec2(-dx,0.0)*offsets[i]) * weights[i]/(2.0*summ);
        }

        return result;

}

/** Приводит глубину к [0;1]
  */
float linearizeDepth(float depth, float farClipPlane, float nearClipPlane) {
        return (2.0*nearClipPlane)/(farClipPlane + nearClipPlane - depth*(farClipPlane - nearClipPlane));
}

subroutine (RenderPassType)
vec4 pass1() {
        return vec4(phongModel(vec3(vPosition), vNormal),1.0);
}

subroutine (RenderPassType)
vec4 pass2() {
        float depth = linearizeDepth(texture2D(depthTexture, texCoord).r, 100.0, 0.05);
        return blurHorizontal(pow(20.0*depth, 2.0));
}

subroutine (RenderPassType)
vec4 pass3() {
        float depth = linearizeDepth(texture2D(depthTexture, texCoord).r, 100.0, 0.05);
        return blurVertical(pow(20.0*depth, 2.0));
}

void main() {
        FragColor = renderPass();
}
