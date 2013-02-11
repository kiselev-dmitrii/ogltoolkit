#include "TestScene.h"

TestScene::TestScene() { }

TestScene::~TestScene() {
}

void TestScene::init() {
        glClearColor(0.9, 0.9, 0.9, 1.0);

        m_cubemapProgram = new GpuProgram("resources/shaders/makeCubemap");
        m_cubemapProgram->bind();

        m_inputTexture = new TextureCube("resources/images/room/", "jpg");
        m_sampler = new TextureUnit();

        m_sampler->bind();
        m_inputTexture->bind();

        m_cubemapProgram->setUniform("sampler", m_sampler->number());
        m_cubemapProgram->setUniform("size", 10.0f);

        initQuad();

        m_outputPosX = new Texture2D(512, 512);
        m_rbo = new Renderbuffer(512, 512, RenderbufferFormat::DEPTH_24);

        string sides[] = {"posx", "negx", "posy", "negy", "posz", "negz"};

        m_fbo = new Framebuffer();
        m_fbo->attachAsColorBuffer(*m_outputPosX);
        m_fbo->attachAsDepthBuffer(*m_rbo);
        m_fbo->bind();
                for(int i=0; i<6; ++i) {
                        m_cubemapProgram->setSubroutine(ShaderType::FRAGMENT_SHADER, sides[i]);

                        glViewport(0,0, 512, 512);
                        glClear(GL_COLOR_BUFFER_BIT);
                        drawQuad();

                        Image img(*m_outputPosX);
                        img.save("output/"+sides[i]+".png");
                }
        m_fbo->unbind();

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
