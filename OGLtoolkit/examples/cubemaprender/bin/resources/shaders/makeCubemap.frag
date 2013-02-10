#version 400

in vec2 texCoord;

layout (location = 0) out vec4 FragColor;

uniform samplerCube sampler;
uniform float size;

subroutine vec4 RenderCubeSide(vec3);
subroutine uniform RenderCubeSide renderSide;

subroutine (RenderCubeSide)
vec4 renderDiffuseSide(vec3 normal) {
        vec4 summ = vec4(0.0);
        // Проходим по верхушке
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,j,1.0));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += max(0.0, dot(lightPos,normal))*lightColor;
                }
        }
        //снизу
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,j,-1.0));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += max(0.0, dot(lightPos,normal))*lightColor;
                }
        }
        // справа
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,1.0,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += max(0.0, dot(lightPos,normal))*lightColor;
                }
        }
        // слева
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,-1.0,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += max(0.0, dot(lightPos,normal))*lightColor;
                }
        }
        //спереди
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(1.0,i,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += max(0.0, dot(lightPos,normal))*lightColor;
                }
        }
        //сзади
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(-1.0,i,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += max(0.0, dot(lightPos,normal))*lightColor;
                }
        }

        summ /= pow(size,2)*6;

        return summ;
}

subroutine (RenderCubeSide)
vec4 renderSpecularSide(vec3 view) {
        float shininess = 80.0f;

        vec4 summ = vec4(0.0);
        // Проходим по верхушке
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,j,1.0));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,view)),shininess) * lightColor;
                }
        }
        //снизу
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,j,-1.0));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,view)),shininess) * lightColor;
                }
        }
        // справа
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,1.0,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,view)),shininess) * lightColor;
                }
        }
        // слева
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,-1.0,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,view)),shininess) * lightColor;
                }
        }
        //спереди
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(1.0,i,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,view)),shininess) * lightColor;
                }
        }
        //сзади
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(-1.0,i,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,view)),shininess) * lightColor;
                }
        }

        summ /= pow(size,2)*0.1;
        return summ;
}

void main() {
        // Рендерим negz
        vec3 normal = normalize(vec3(1.0, texCoord.x, texCoord.y));
        FragColor = renderSide(normal);
}
