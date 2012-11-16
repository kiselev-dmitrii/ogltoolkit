#include "TestScene.h"
#include "lib/Subsystems/Application.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Debug/Debug.h"
#include "lib/Framework/Render.h"

TestScene::TestScene() { }

TestScene::~TestScene() {
        delete m_reflection;
        delete m_camera;
        delete m_tuCubeMap;
        delete m_eTeapot;
        delete m_tcEnvironment;
}

void TestScene::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        m_reflection = new GpuProgram("shaders/cubeMapping.vert", "shaders/cubeMapping.frag");
        Render::instance()->setCurrentProgram(m_reflection);

        m_camera = new Camera();
        m_camera->setPosition(vec3(3,3,3));
        m_camera->setTarget(vec3(0,0,0));
        Render::instance()->setCurrentCamera(m_camera);

        m_tuCubeMap = new TextureUnit();
}

void TestScene::initTeapotModel() {
        m_eTeapot = new Entity(Mesh("meshes/model.obj", 0, MeshFlags::NORMALS | MeshFlags::TEXCOORDS));
        m_tcEnvironment = new TextureCube("images/church", "jpg");

        m_reflection->setUniform("mirror.baseColor", vec3(0.5,0.5,0.0));
        m_reflection->setUniform("mirror.reflectFactor", 0.9f);
}

void TestScene::initSkybox() {
        m_eSkybox = new Entity(Mesh("meshes/cube.obj", 0, MeshFlags::NORMALS | MeshFlags::TEXCOORDS));
        m_eSkybox->setPivot(vec3(0.5, 0.5, 0.5));
        m_eSkybox->setScale(vec3(100,100,100));
}

void TestScene::init() {
        Mouse::hide();

        initRender();

        initTeapotModel();
        initSkybox();
}

void TestScene::resize(int w, int h) {
        glViewport(0,0,w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void TestScene::update(float deltaTime) {
        m_eTeapot->rotate(vec3(0,0,deltaTime*100));
}

void TestScene::renderTeapotModel() {
        m_tuCubeMap->bind();
        m_tcEnvironment->bind();

        m_reflection->setUniform("isDrawSkybox", false);
        Render::instance()->render(m_eTeapot);
}

void TestScene::renderSkybox() {
        m_tuCubeMap->bind();
        m_tcEnvironment->bind();

        m_reflection->setUniform("isDrawSkybox", true);
        Render::instance()->render(m_eSkybox);
}

void TestScene::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_reflection->setUniform("wCameraPosition", m_camera->position());
        renderSkybox();
        renderTeapotModel();
}

void TestScene::onMouseMove(int x, int y) {
        ivec2 pos = ivec2(x,y);
        Mouse::setPos(Application::instance()->window()->center());
        vec2 delta = vec2(Application::instance()->window()->center() - pos);
        m_camera->rotateWithMouse(delta);
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
