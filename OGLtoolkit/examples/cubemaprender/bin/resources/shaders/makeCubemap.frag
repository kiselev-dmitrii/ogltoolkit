#version 400

in vec2 texCoord;

layout (location = 0) out vec4 FragColor;

uniform samplerCube sampler;
uniform float size;

subroutine vec4 RenderSide();
subroutine uniform RenderSide renderSide;

vec4 diffuse(vec3 normal) {
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

vec4 specular(vec3 view) {
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

vec4 renderLighting(vec3 vec) {
        return specular(vec);
}

subroutine (RenderSide)
vec4 posx() {
        vec3 normal = normalize(vec3(1.0, texCoord.x, texCoord.y));
        return renderLighting(normal);
}

subroutine (RenderSide)
vec4 negx() {
        vec3 normal = normalize(vec3(-1.0, texCoord.x, texCoord.y));
        return renderLighting(normal);
}

subroutine (RenderSide)
vec4 posy() {
        vec3 normal = normalize(vec3(texCoord.x, 1.0, texCoord.y));
        return renderLighting(normal);
}

subroutine (RenderSide)
vec4 negy() {
        vec3 normal = normalize(vec3(texCoord.x, -1.0, texCoord.y));
        return renderLighting(normal);
}

subroutine (RenderSide)
vec4 posz() {
        vec3 normal = normalize(vec3(texCoord.x, texCoord.y, 1.0));
        return renderLighting(normal);
}

subroutine (RenderSide)
vec4 negz() {
        vec3 normal = normalize(vec3(texCoord.x, texCoord.y, -1.0));
        return renderLighting(normal);
}




void main() {
        FragColor = renderSide();
}
