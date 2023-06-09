#include "EdgeTestScene.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Application.h"
#include "lib/Framework/Render.h"
#include "lib/Debug/Debug.h"

EdgeTestScene::EdgeTestScene() {
        m_secondPass = "sobelOperator";
}

EdgeTestScene::~EdgeTestScene() {
}

void EdgeTestScene::init() {
        initRender();
        initQuad();
        initPlane();
        initTeapot();
}

void EdgeTestScene::resize(int w, int h) {
        glViewport(0,0,w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void EdgeTestScene::update(float deltaTime) {
        SHOW(1.0/deltaTime);
}

void EdgeTestScene::render() {
        pass1();
        pass2();
}

void EdgeTestScene::onKeyPress(int key) {
        switch(key) {
                case 'W':
                        m_camera->moveForward(0.1);
                        break;
                case 'S':
                        m_camera->moveForward(-0.1);
                        break;
                case 'D':
                        m_camera->moveRight(0.1);
                        break;
                case 'A':
                        m_camera->moveRight(-0.1);
                        break;

                case '1':
                        m_secondPass = "identityOperator";
                        break;
                case '2':
                        m_secondPass = "sobelOperator";
                        break;
        }
}

void EdgeTestScene::onMouseMove(int x, int y) {
        Mouse::hide();

        ivec2 pos = ivec2(x,y);
        Mouse::setPos(Application::instance()->window()->center());
        vec2 delta = vec2(Application::instance()->window()->center() - pos);
        m_camera->rotateWithMouse(delta);
}

void EdgeTestScene::initRender() {
        glClearColor(0.9,0.9,0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        m_camera = new Camera();
        Render::instance()->setCurrentCamera(m_camera);
        m_camera->setPosition(vec3(10,10,10));
        m_camera->setTarget(vec3(0,0,0));

        m_program = new GpuProgram("resources/shaders/edges");
        Render::instance()->setCurrentProgram(m_program);
        m_program->setUniform("light.position", vec3(10,10,10));
        m_program->setUniform("light.color", vec3(1.0, 1.0, 1.0));
        m_program->setUniform("textureWidth", 800.0f);
        m_program->setUniform("textureHeight", 600.0f);

        // Создаем FBO с присоединенной texture и rbo
        m_texture = new Texture2D(800, 600);
        m_rbo = new Renderbuffer(800, 600, RenderbufferFormat::DEPTH_24);

        m_fbo = new Framebuffer();
        m_fbo->attachAsColorBuffer(*m_texture);
        m_fbo->attachAsDepthBuffer(*m_rbo);

        //
        m_sampler = new TextureUnit();
        m_sampler->bindTexture(*m_texture);
        m_program->setUniform("inputTexture", m_sampler->number());
}

void EdgeTestScene::initPlane() {
        m_ePlane = new Entity("resources/meshes/cube.obj");
        m_ePlane->setScale(vec3(100,100, 0.1));
        m_ePlane->setPosition(vec3(0,0,-1));
}

void EdgeTestScene::initTeapot() {
        m_eTeapot = new Entity(Mesh("resources/meshes/suzanne.obj", 0));
        m_eTeapot->setOrientation(vec3(90,90,0));
        m_eTeapot->setScale(vec3(0.5,0.5,0.5));
}

void EdgeTestScene::renderTeapot() {
        m_program->setUniform("material.ambient", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.diffuse", vec3(1.0,1.0,0.3));
        m_program->setUniform("material.specular", vec3(1.0,1.0,1.0));
        m_program->setUniform("material.shininess", 80.0f);

        Render::instance()->render(m_eTeapot);
}

void EdgeTestScene::renderPlane() {
        m_program->setUniform("material.ambient", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.diffuse", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.specular", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.shininess", 0.0f);

        Render::instance()->render(m_ePlane);
}

void EdgeTestScene::initQuad() {
        // 1 VBO на все провсе
        float vertices[] = {
                -1, -1, 0,
                 0,  0,

                -1,  1, 0,
                 0,  1,

                 1,  1, 0,
                 1,  1,

                 1, -1, 0,
                 1,  0
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

void EdgeTestScene::drawQuad() {
        m_program->setUniform("V", mat4(1));
        m_program->setUniform("M", mat4(1));
        m_program->setUniform("MV", mat4(1));
        m_program->setUniform("MVP", mat4(1));
        m_program->setUniform("N", mat3(1));

        m_vao->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid *) 0);
}

void EdgeTestScene::pass1() {
        m_program->setSubroutine(ShaderType::FRAGMENT_SHADER, "phongLighting");

        m_fbo->bind();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                renderPlane();
                renderTeapot();
        m_fbo->unbind();
}

void EdgeTestScene::pass2() {
        m_program->setSubroutine(ShaderType::FRAGMENT_SHADER, m_secondPass);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawQuad();
}
