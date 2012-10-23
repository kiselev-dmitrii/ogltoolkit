#include "TriangleScene.h"
#include "lib/Debug/Debug.h"
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;
using glm::vec4;

TriangleScene::TriangleScene() {
}

void TriangleScene::init() {
        glClearColor(0,0,0,0);

        // GpuProgram
        m_program = new GpuProgram();
        m_program->compileShaderFromFile("shaders/basic.vert", ShaderType::VERTEX_SHADER);
        m_program->compileShaderFromFile("shaders/basic.frag", ShaderType::FRAGMENT_SHADER);
        m_program->link();
        m_program->bind();

        // VAO и VBO
        float positions[] = {
                -1, -1, 0,
                -1,  1, 0,
                 1,  1, 0,
                 1, -1, 0

        };
        m_vboPositions = new VertexBuffer();
        m_vboPositions->uploadData(positions, 18*sizeof(float), Hint::STATIC_DRAW);

        float texCoords[] = {
                0, 0,
                0, 1,
                1, 1,
                1, 0
        };
        m_vboTexCoord = new VertexBuffer();
        m_vboTexCoord->uploadData(texCoords, 12*sizeof(float), Hint::STATIC_DRAW);

        // IBO
        GLuint indices[6] = { 0, 1, 2, 2, 3, 0 };
        m_ibo = new IndexBuffer();
        m_ibo->uploadData(indices, 6*sizeof(GLuint), Hint::STATIC_DRAW);

        // Устанавливаем состояние vao
        m_vao = new VertexArray();
        m_vao->bind();
                m_ibo->bind();
                // Говорим, что будем использовать индексный буфер с этим vao

                // Говорим OpenGL'у как интерпретировать данные в VBO
                m_vboPositions->setAttribAssociation("vertexPosition", 3, GL_FLOAT);
                m_vboTexCoord->setAttribAssociation("vertexTexCoord", 2, GL_FLOAT);
        m_vao->unbind();


        //Данные для UBO
        m_blobSettigs = new UniformBlock(m_program, "BlobSettings");
        m_blobSettigs->setMember("innerColor", vec4(1,1, 0.75, 1));
        m_blobSettigs->setMember("outerColor", vec4(0,0, 0, 0));
        m_blobSettigs->setMember("innerRadius", 0.3f);
        m_blobSettigs->setMember("outerRadius", 0.4f);

        m_uboBlobSettings = new UniformBuffer();
        m_uboBlobSettings->uploadData(m_blobSettigs, Hint::DYNAMIC_DRAW);
        m_uboBlobSettings->bindToBlock(m_blobSettigs);
}

TriangleScene::~TriangleScene() {
        delete m_program;
        delete m_vao;
        delete m_vboPositions;
        delete m_vboTexCoord;
        delete m_uboBlobSettings;
        delete m_blobSettigs;
        delete m_ibo;
}

void TriangleScene::resize(int w, int h) {
        glViewport(0,0, w,h);
}

void TriangleScene::update(float t) {
}

void TriangleScene::render() {
        glClear(GL_COLOR_BUFFER_BIT);

        // Рендерим данные в соответствии с VAO
        glBindVertexArray(m_vao->handle());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid *) 0);
}

