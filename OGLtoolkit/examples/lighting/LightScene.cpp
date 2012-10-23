#include "LightScene.h"
#include "glm/gtx/transform.hpp"

LightScene::LightScene() {}

LightScene::~LightScene() {
        delete m_mesh;
        delete m_vboMesh;
        delete m_iboMesh;
        delete m_vaoMesh;
        delete m_program;
}

void LightScene::init() {
        glClearColor(0,0,0,0);

        //GpuProgram
        m_program = new GpuProgram();
        m_program->compileShaderFromFile("shaders/lighting.vert", ShaderType::VERTEX_SHADER);
        m_program->compileShaderFromFile("shaders/lighting.frag", ShaderType::FRAGMENT_SHADER);
        m_program->link();
        m_program->bind();

        //Создаем Меш
        m_mesh = new Mesh();
        m_mesh->loadMeshFromFile("meshes/model.obj");

        //VBO и IBO
        m_vboMesh = new VertexBuffer();
        m_vboMesh->uploadData(m_mesh->vertices(), m_mesh->verticesSize(), Hint::STATIC_DRAW);
        m_iboMesh = new IndexBuffer();
        m_iboMesh->uploadData(m_mesh->indices(), m_mesh->indicesSize(), Hint::STATIC_DRAW);

        // Создаем VAO и ассоциируем с ним данные VBO и IBO
        m_vaoMesh = new VertexArray();
        m_vaoMesh->bind();
                //Задаем интерпретацию VBO
                m_vboMesh->setAttribAssociation("vertexPosition", 3, GL_FLOAT, 0, sizeof(Vertex));
                m_vboMesh->setAttribAssociation("vertexNormal", 3, GL_FLOAT, sizeof(vec3), sizeof(Vertex));
                m_vboMesh->setAttribAssociation("vertexTexCoord", 2, GL_FLOAT, 2*sizeof(vec3), sizeof(Vertex));

                m_iboMesh->bind();
        m_vaoMesh->unbind();
}

void LightScene::resize(int w, int h) {
        glViewport(0, 0, w, h);
}

void LightScene::update(float t) {
        mat3 normalMatrix = mat3(1);
        mat4 MVPMatrix = glm::scale(mat4(1), vec3(0.5));
        mat4 ModelViewMatrix = glm::scale(mat4(1), vec3(0.5));
        MVPMatrix = glm::rotate(MVPMatrix, 30.0f, vec3(1,0,1));
        MVPMatrix = glm::rotate(MVPMatrix, 30.0f, vec3(1,0,0));

        vec3 lightPosition = vec3(1,1,1);
        vec3 Kd = vec3(0.5, 1.0, 1.0);
        vec3 Ld = vec3(1.0, 1.0, 1.0);

        m_program->setUniform("NormalMatrix", normalMatrix);
        m_program->setUniform("MVPMatrix", MVPMatrix);
        m_program->setUniform("ModelViewMatrix", ModelViewMatrix);
        m_program->setUniform("lightPosition", lightPosition);
        m_program->setUniform("Kd", Kd);
        m_program->setUniform("Ld", Ld);
}

void LightScene::render() {
        glClear(GL_COLOR_BUFFER_BIT);

        m_vaoMesh->bind();
        glDrawElements(GL_TRIANGLES, m_mesh->indicesCount(), GL_UNSIGNED_INT, (GLvoid *) 0);
}
