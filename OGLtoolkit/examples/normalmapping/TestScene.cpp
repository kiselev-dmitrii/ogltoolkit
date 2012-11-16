#include "TestScene.h"
#include "lib/Subsystems/Application.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Debug/Debug.h"
#include "lib/Framework/Render.h"

TestScene::TestScene() { }

TestScene::~TestScene() {
        delete m_normalMapping;
        delete m_camera;
        delete m_tuBase;
        delete m_tuNormalMap;
        delete m_eOgre;
        delete m_tOgre;
        delete m_tOgreNormals;
}

void TestScene::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        m_normalMapping = new GpuProgram();
        m_normalMapping->compileShaderFromFile("shaders/normalMapping.vert", ShaderType::VERTEX_SHADER);
        m_normalMapping->compileShaderFromFile("shaders/normalMapping.frag", ShaderType::FRAGMENT_SHADER);
        m_normalMapping->link();
        Render::instance()->setCurrentProgram(m_normalMapping);

        m_camera = new Camera();
        m_camera->setPosition(vec3(3,3,3));
        m_camera->setTarget(vec3(0,0,0));
        Render::instance()->setCurrentCamera(m_camera);

        m_tuBase = new TextureUnit();
        m_tuNormalMap = new TextureUnit();
}

void TestScene::initLight() {
        GpuProgram* curProgram = Render::instance()->currentProgram();

        curProgram->setUniform("light.wPosition", vec3(-10,-10,6));
        curProgram->setUniform("light.color", vec3(0.9, 0.9, 0.9));
}

void TestScene::initOgreModel() {
        m_eOgre = new Entity("meshes/model.obj");
        m_eOgre->rotate(vec3(90,-40,0));

        m_tOgre = new Texture2D("images/ogre_diffuse.png");
        m_tOgreNormals = new Texture2D("images/ogre_normalmap.png");
}

void TestScene::init() {
        Mouse::hide();

        initRender();
        initLight();

        initOgreModel();
}

void TestScene::resize(int w, int h) {
        glViewport(0,0,w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void TestScene::update(float deltaTime) {
}

void TestScene::renderOgreModel() {
        m_tuBase->bind();
        m_tOgre->bind();

        m_tuNormalMap->bind();
        m_tOgreNormals->bind();

        Render::instance()->currentProgram()->setUniform("material.ambient", vec3(0.2));
        Render::instance()->currentProgram()->setUniform("material.specular", vec3(0.1));
        Render::instance()->currentProgram()->setUniform("material.shininess", 10);

        Render::instance()->currentProgram()->setUniform("baseSampler", m_tuBase->number());
        Render::instance()->currentProgram()->setUniform("normalSampler", m_tuNormalMap->number());

        Render::instance()->render(m_eOgre);
}

void TestScene::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderOgreModel();
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
