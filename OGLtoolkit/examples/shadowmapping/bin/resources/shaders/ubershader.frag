#version 400

in vec4 vPosition;
in vec3 vNormal;
in vec2 texCoord;
#ifdef SHADOW_MAPPING
in vec4 vShadowCoord;
#endif SHADOW_MAPPING

layout (location = 0) out vec4 FragColor;

#ifdef PHONG_LIGHT_MODEL
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
#endif PHONG_LIGHT_MODEL

#ifdef SHADOW_MAPPING
uniform sampler2DShadow shadowMap;
#endif SHADOW_MAPPING

#ifdef DRAW_QUAD
uniform sampler2D baseTexture;
#endif DRAW_QUAD

#ifndef DRAW_QUAD
uniform mat4 _V;
#endif DRAW_QUAD

#ifdef PHONG_LIGHT_MODEL
vec3 phongModel(vec3 pos, vec3 norm) {
        vec3 vLightPos = vec3(_V * vec4(light.position,1.0));

        vec3 s = normalize(vLightPos - pos);
        vec3 v = normalize(-pos.xyz);
        vec3 r = reflect(-s, norm);

        float sDotN = max(dot(s,norm), 0.0);
        vec3 diffuse = light.color * material.diffuse * sDotN;

        vec3 specular = vec3(0.0);
        if (sDotN > 0.0) {
                specular = light.color * material.specular * pow(max(dot(r,v), 0.0), material.shininess);
        }

        return diffuse + specular;
}
#endif PHONG_LIGHT_MODEL

#ifdef SHADOW_MAPPING
vec3 shadeWithShadow() {
        vec3 ambient = light.color * material.ambient;
        #ifdef PHONG_LIGHT_MODEL
        vec3 spec_diffuse = phongModel(vPosition, vNormal);
        #endif

        float summ = 0;
        summ += textureProjOffset(shadowMap, vShadowCoord, ivec2(-1,-1));
        summ += textureProjOffset(shadowMap, vShadowCoord, ivec2(-1,1));
        summ += textureProjOffset(shadowMap, vShadowCoord, ivec2(1,1));
        summ += textureProjOffset(shadowMap, vShadowCoord, ivec2(1,-1));
        summ /= 4.0;

        return spec_diffuse*summ + ambient;
}
#endif SHADOW_MAPPING

#ifdef DRAW_QUAD
float linearizeDepth(float depth, float farClipPlane, float nearClipPlane) {
        return (2.0*nearClipPlane)/(farClipPlane + nearClipPlane - depth*(farClipPlane - nearClipPlane));
}
#endif DRAW_QUAD

void main() {
        FragColor = vec4(0.0);

        #ifdef DRAW_QUAD
        FragColor += vec4(linearizeDepth(texture(baseTexture, texCoord).r, 100, 0.05));
        #endif DRAW_QUAD

        #ifdef RECORD_DEPTH
        #endif RECORD_DEPTH

        #ifdef LIGHTING
        FragColor = vec4(shadeWithShadow(), 1.0);
        #endif LIGHTING
}
