#include "BlurTestScene.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Keyboard.h"
#include "lib/Subsystems/Application.h"
#include "lib/Framework/Render.h"
#include "lib/Utils/Debug.h"
#include "lib/Utils/StringUtils.h"
using namespace StringUtils;

BlurTestScene::BlurTestScene() {
}

BlurTestScene::~BlurTestScene() {
}

void BlurTestScene::init() {
        Mouse::hide();

        initRender();
        initQuad();
        initPlane();
        initTeapot();
        initMonkey();
}

void BlurTestScene::resize(int w, int h) {
        glViewport(0,0,w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void BlurTestScene::update(float deltaTime) {
        SHOW(1.0/deltaTime);

        // Обновление ориентации камеры
        ivec2 pos = Mouse::pos();
        Mouse::setPos(Application::window()->center());
        vec2 delta = vec2(Application::window()->center() - pos);
        m_camera->rotateWithMouse(delta);

        // Обновление позиции камеры
        float speed = 5;
        if(Keyboard::isKeyPressed('W'))  m_camera->moveForward(speed*deltaTime);
        if(Keyboard::isKeyPressed('S'))  m_camera->moveForward(-speed*deltaTime);
        if(Keyboard::isKeyPressed('D'))  m_camera->moveRight(speed*deltaTime);
        if(Keyboard::isKeyPressed('A'))  m_camera->moveRight(-speed*deltaTime);
}

void BlurTestScene::render() {
        pass1();
        pass2();
        pass3();
}

void BlurTestScene::initRender() {
        glClearColor(0.9,0.9,0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        m_camera = new Camera();
        Render::instance()->setCurrentCamera(m_camera);
        m_camera->setPosition(vec3(10,10,10));
        m_camera->setTarget(vec3(0,0,0));

        m_program = new GpuProgram("resources/shaders/blur");
        Render::instance()->setCurrentProgram(m_program);
        m_program->setUniform("light.position", vec3(10,10,10));
        m_program->setUniform("light.color", vec3(1.0, 1.0, 1.0));
        m_program->setUniform("textureWidth", 800.0f);
        m_program->setUniform("textureHeight", 600.0f);

        // Создаем FBO с присоединенной texture и rbo
        m_texture1 = new ColorTexture2D(800, 600);
        m_depthTexture = new DepthTexture2D(800, 600);
        m_fbo1 = new Framebuffer();
        m_fbo1->attachAsColorBuffer(m_texture1);
        m_fbo1->attachAsDepthBuffer(m_depthTexture);

        m_texture2 = new ColorTexture2D(800, 600);
        m_fbo2 = new Framebuffer();
        m_fbo2->attachAsColorBuffer(m_texture2);

        //
        m_sampler = new TextureUnit();
        m_program->setUniform("inputTexture", m_sampler->number());

        m_depthSampler = new TextureUnit();
        m_program->setUniform("depthTexture", m_depthSampler->number());

}

void BlurTestScene::initPlane() {
        m_ePlane = new Entity("resources/meshes/cube.obj");
        m_ePlane->setScale(vec3(100,100, 0.1));
        m_ePlane->setPosition(vec3(0,0,-1));
}

void BlurTestScene::initTeapot() {
        m_eTeapot = new Entity(Mesh("resources/meshes/teapot.obj", 1));
        m_eTeapot->setOrientation(vec3(90,90,0));
        m_eTeapot->setScale(vec3(0.5,0.5,0.5));
}

void BlurTestScene::initMonkey() {
        m_eMonkey = new Entity(Mesh("resources/meshes/suzanne.obj"));
        m_eMonkey->setOrientation(vec3(90,90,0));
        m_eMonkey->setScale(vec3(2.0,2.0,2.0));
        m_eMonkey->setPosition(vec3(5.0, 5.0, 2.0));
}

void BlurTestScene::renderTeapot() {
        m_program->setUniform("material.ambient", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.diffuse", vec3(1.0,1.0,0.3));
        m_program->setUniform("material.specular", vec3(1.0,1.0,1.0));
        m_program->setUniform("material.shininess", 80.0f);

        Render::instance()->render(m_eTeapot);
}

void BlurTestScene::renderPlane() {
        m_program->setUniform("material.ambient", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.diffuse", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.specular", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.shininess", 0.0f);

        Render::instance()->render(m_ePlane);
}

void BlurTestScene::renderMonkey() {
        m_program->setUniform("material.ambient", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.diffuse", vec3(0.9,0.3,0.3));
        m_program->setUniform("material.specular", vec3(0.3,0.3,0.3));
        m_program->setUniform("material.shininess", 0.0f);

        Render::instance()->render(m_eMonkey);
}

void BlurTestScene::initQuad() {
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

void BlurTestScene::drawQuad() {
        m_program->setUniform("V", mat4(1));
        m_program->setUniform("M", mat4(1));
        m_program->setUniform("MV", mat4(1));
        m_program->setUniform("MVP", mat4(1));
        m_program->setUniform("N", mat3(1));

        m_vao->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid *) 0);
}

void BlurTestScene::pass1() {
        m_program->setSubroutine(ShaderType::FRAGMENT_SHADER, "pass1");

        m_fbo1->bind();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                renderTeapot();
                m_eTeapot->setPosition(vec3(1,10,0));
                renderTeapot();
                m_eTeapot->setPosition(vec3(0,0,0));
                renderMonkey();
                renderPlane();
        m_fbo1->unbind();
}

void BlurTestScene::pass2() {
        m_sampler->bindTexture(m_texture1);
        m_depthSampler->bindTexture(m_depthTexture);
        m_program->setSubroutine(ShaderType::FRAGMENT_SHADER, "pass2");

        m_fbo2->bind();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                drawQuad();
        m_fbo2->unbind();

        m_depthSampler->unbindTexture(m_depthTexture);
}

void BlurTestScene::pass3() {
        m_sampler->bindTexture(m_texture2);
        m_depthSampler->bindTexture(m_depthTexture);
        m_program->setSubroutine(ShaderType::FRAGMENT_SHADER, "pass3");

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawQuad();

        m_depthSampler->unbindTexture(m_depthTexture);
}
