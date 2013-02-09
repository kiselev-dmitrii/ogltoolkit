#version 400

in vec2 texCoord;

layout (location = 0) out vec4 FragColor;

uniform samplerCube sampler;
uniform float size;

void main() {
        // Рендерим negz
        vec3 normal = normalize(vec3(texCoord.x,texCoord.y,-1.0));

        vec4 summ = 0.0;
        // Проходим по верхушке
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,j,1.0));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,normal)),80)*lightColor;
                }
        }
        //снизу
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,j,-1.0));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,normal)),80)*lightColor;
                }
        }
        // справа
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,1.0,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,normal)),80)*lightColor;
                }
        }
        // слева
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(i,-1.0,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,normal)),80)*lightColor;
                }
        }
        //спереди
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(1.0,i,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,normal)),80)*lightColor;
                }
        }
        //сзади
        for(float i=-1; i<=1; i+=1.0/size) {
                for (float j=-1; j<=1; j+=1.0/size) {
                        vec3 lightPos = normalize(vec3(-1.0,i,j));
                        vec4 lightColor = textureCube(sampler, lightPos);

                        summ += pow(max(0.0, dot(lightPos,normal)),80)*lightColor;
                }
        }

        summ /= pow(size,2)*0.2;

        FragColor = summ;
}
