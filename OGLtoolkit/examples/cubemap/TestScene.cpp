#include "TestScene.h"
#include "lib/Subsystems/Application.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Debug/Debug.h"
#include "lib/Framework/Render.h"

TestScene::TestScene() { }

TestScene::~TestScene() {
        delete m_glassProgram;
        delete m_camera;
        delete m_eTeapot;
        delete m_eBullet;
        delete m_eSkybox;
        delete m_tcEnvironment;
        delete m_tuCubeMap;
}

void TestScene::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        m_glassProgram = new GpuProgram("resources/shaders/cubeMapping.vert", "resources/shaders/cubeMapping.frag");
        Render::instance()->setCurrentProgram(m_glassProgram);

        m_camera = new Camera();
        m_camera->setPosition(vec3(3,3,3));
        m_camera->setTarget(vec3(0,0,0));
        Render::instance()->setCurrentCamera(m_camera);

        m_tuCubeMap = new TextureUnit();
        m_tcEnvironment = new TextureCube("resources/images/lawn", "jpg");
}

void TestScene::initBulletModel() {
        m_eBullet = new Entity(Mesh("resources/meshes/teapot.obj", 1, MeshFlags::NORMALS | MeshFlags::TEXCOORDS));
        m_eBullet->setPosition(vec3(0,15,0));
        m_eBullet->setOrientation(vec3(90,90,0));
}

void TestScene::initTeapotModel() {
        m_eTeapot = new Entity(Mesh("resources/meshes/teapot.obj", 1, MeshFlags::NORMALS | MeshFlags::TEXCOORDS));
        m_eTeapot->setOrientation(vec3(90,90,0));
}

void TestScene::initSkybox() {
        m_eSkybox = new Entity(Mesh("resources/meshes/cube.obj", 0, MeshFlags::NORMALS | MeshFlags::TEXCOORDS));
        m_eSkybox->setPivot(vec3(0.5, 0.5, 0.5));
        m_eSkybox->setScale(vec3(100,100,100));
}

void TestScene::init() {
        Mouse::hide();

        initRender();

        initTeapotModel();
        initBulletModel();
        initSkybox();
}

void TestScene::resize(int w, int h) {
        glViewport(0,0,w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void TestScene::update(float deltaTime) {
        //m_eTeapot->rotate(vec3(deltaTime*10,deltaTime*100,0));
        //SHOW(1.0/deltaTime);
}

void TestScene::renderBulletModel() {
        //Биндим в TextureUnit m_tuCubeMap текстиру m_tcEnvironment
        m_tuCubeMap->bind();
        m_tcEnvironment->bind();

        m_glassProgram->setUniform("isDrawSkybox", false);
        m_glassProgram->setUniform("cubemap", m_tuCubeMap->number());
        m_glassProgram->setUniform("material.ratio", 0.1f);
        m_glassProgram->setUniform("material.reflectFactor", 3.0f);
        Render::instance()->render(m_eBullet);
}

void TestScene::renderTeapotModel() {
        m_tuCubeMap->bind();
        m_tcEnvironment->bind();

        m_glassProgram->setUniform("isDrawSkybox", false);
        m_glassProgram->setUniform("cubemap", m_tuCubeMap->number());
        m_glassProgram->setUniform("material.ratio", 0.75f);
        m_glassProgram->setUniform("material.reflectFactor", 5.0f);
        Render::instance()->render(m_eTeapot);
}

void TestScene::renderSkybox() {
        m_tuCubeMap->bind();
        m_tcEnvironment->bind();

        m_glassProgram->setUniform("isDrawSkybox", true);
        m_glassProgram->setUniform("cubemap", m_tuCubeMap->number());
        Render::instance()->render(m_eSkybox);
}

void TestScene::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_glassProgram->setUniform("wCameraPosition", m_camera->position());
        renderSkybox();
        renderTeapotModel();
        renderBulletModel();
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
