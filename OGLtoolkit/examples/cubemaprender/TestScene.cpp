#include "TestScene.h"

TestScene::TestScene() { }

TestScene::~TestScene() {
}

void TestScene::init() {
        glClearColor(0.9, 0.9, 0.9, 1.0);

        m_cubemapProgram = new GpuProgram("resources/shaders/makeCubemap");
        m_cubemapProgram->bind();

        m_inputTexture = new TextureCube("resources/images/church/", "jpg");
        m_sampler = new TextureUnit();

        m_sampler->bind();
        m_inputTexture->bind();

        m_cubemapProgram->setUniform("sampler", m_sampler->number());
        m_cubemapProgram->setUniform("size", 50.0f);

        initQuad();

        glViewport(0,0, 600, 600);
        glClear(GL_COLOR_BUFFER_BIT);
        drawQuad();
}

void TestScene::resize(int w, int h) {
        glViewport(0, 0, w, h);
}

void TestScene::update(float deltaTime) {
}

void TestScene::render() {
}

void TestScene::initQuad() {
        // 1 VBO на все провсе
        float vertices[] = {
                -1, -1, 0,
                -1, -1,

                -1,  1, 0,
                -1,  1,

                 1,  1, 0,
                 1,  1,

                 1, -1, 0,
                 1, -1
        };
        GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

        m_vbo = new VertexBuffer();
        m_ibo = new IndexBuffer();
        m_vbo->uploadData(vertices, 4*5*sizeof(float), Hint::STATIC_DRAW);
        m_ibo->uploadData(indices, 6*sizeof(uint), Hint::STATIC_DRAW);

        m_vao = new VertexArray();
        m_vao->bind();
                m_vbo->setAttribAssociation("vertexPosition", 3, GL_FLOAT, 0, 5*sizeof(float));
                m_vbo->setAttribAssociation("vertexTexCoord", 2, GL_FLOAT, 3*sizeof(float), 5*sizeof(float));
                m_ibo->bind();
        m_vao->unbind();
}

void TestScene::drawQuad() {
        m_vao->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid *) 0);
}
