#include "TestScene.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Application.h"
#include "lib/Framework/Render.h"

TestScene::TestScene() { }

TestScene::~TestScene() {
}

void TestScene::init() {
        initRender();
        initPlane();
        initTeapot();
}

void TestScene::resize(int w, int h) {
        glViewport(0,0,w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void TestScene::update(float deltaTime) {  }

void TestScene::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderPlane();
        renderTeapot();
}

void TestScene::onKeyPress(int key) {
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
        }
}

void TestScene::onMouseMove(int x, int y) {
        Mouse::hide();

        ivec2 pos = ivec2(x,y);
        Mouse::setPos(Application::instance()->window()->center());
        vec2 delta = vec2(Application::instance()->window()->center() - pos);
        m_camera->rotateWithMouse(delta);
}

void TestScene::initRender() {
        glClearColor(0.9,0.9,0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        m_tLogo = new Texture2D("resources/images/hl.jpg");
        m_tLogo->setWrapS(WrapMode::CLAMP_TO_BORDER);
        m_tLogo->setWrapT(WrapMode::CLAMP_TO_BORDER);
        m_tuProjTexture = new TextureUnit();
        m_tuProjTexture->bindTexture(*m_tLogo);

        m_camera = new Camera();
        Render::instance()->setCurrentCamera(m_camera);

        m_projector = new GpuProgram("resources/shaders/projector");
        Render::instance()->setCurrentProgram(m_projector);
        mat4 projectorMatrix = calcProjectorMatrix(vec3(10,10,10), vec3(0,0,0), vec3(0,1,0));
        m_projector->setUniform("ProjectorMatrix", projectorMatrix);
        m_projector->setUniform("wCameraPosition", m_camera->position());
        m_projector->setUniform("projectorTexture", m_tuProjTexture->number());
        m_projector->setUniform("light.position", vec3(10,10,10));
        m_projector->setUniform("light.color", vec3(1.0, 1.0, 1.0));
}

void TestScene::initPlane() {
        m_ePlane = new Entity("resources/meshes/cube.obj");
        m_ePlane->setScale(vec3(100,100, 0.1));
        m_ePlane->setPosition(vec3(0,0,-1));
}

void TestScene::initTeapot() {
        m_eTeapot = new Entity(Mesh("resources/meshes/teapot.obj", 1));
        m_eTeapot->setOrientation(vec3(90,90,0));
        m_eTeapot->setScale(vec3(0.5,0.5,0.5));
}

void TestScene::renderTeapot() {
        m_projector->setUniform("wCameraPosition", m_camera->position());

        m_projector->setUniform("material.ambient", vec3(0.3,0.3,0.3));
        m_projector->setUniform("material.diffuse", vec3(1.0,1.0,0.3));
        m_projector->setUniform("material.specular", vec3(1.0,1.0,1.0));
        m_projector->setUniform("material.shininess", 80.0f);

        Render::instance()->render(m_eTeapot);
}

void TestScene::renderPlane() {
        m_projector->setUniform("wCameraPosition", m_camera->position());

        m_projector->setUniform("material.ambient", vec3(0.3,0.3,0.3));
        m_projector->setUniform("material.diffuse", vec3(0.3,0.3,0.3));
        m_projector->setUniform("material.specular", vec3(1.0,1.0,1.0));
        m_projector->setUniform("material.shininess", 0.0f);

        Render::instance()->render(m_ePlane);
}

mat4 TestScene::calcProjectorMatrix(const vec3 &pos, const vec3 &dir, const vec3 &up) {
        mat4 V = glm::lookAt(pos, dir, up);             //переводит из world в видовые для прожектора
        mat4 P = glm::perspective(30.0f, 1.0f, 0.2f, 1000.0f);

        return glm::translate(vec3(0.5f)) * glm::scale(vec3(0.5f)) * P * V;
}
