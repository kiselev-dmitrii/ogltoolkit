#include "FrameWorkTest.h"
#include "lib/Framework/Render.h"
#include "lib/Utils/Debug.h"

FrameWorkTest::FrameWorkTest() {
}

FrameWorkTest::~FrameWorkTest() {
}

void FrameWorkTest::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);
}

void FrameWorkTest::initEntities() {
        m_node1 = new SceneNode("Node1");
        m_node2 = new SceneNode("Node2");
        m_node3 = new SceneNode("Node3");

        m_entityManager = new EntityManager();
        m_entityManager->addMesh(Mesh("resources/meshes/suzanne.obj"), "suzanne");
        m_entityManager->addMesh(Mesh("resources/meshes/teapot.obj"), "teapot");
        m_entityManager->addMesh(Mesh("resources/meshes/cube.obj"), "cube");

        m_entityManager->createEntity("suzanne", "suzanne");
        m_entityManager->createEntity("teapot", "teapot");
        m_entityManager->createEntity("cube", "cube");

        m_entityManager->entity("suzanne")->setNode(m_node1);
        m_entityManager->entity("teapot")->setNode(m_node2);
        m_entityManager->entity("cube")->setNode(m_node3);
}

void FrameWorkTest::initCamera() {
        m_cameraNode = new SceneNode("Camera_node");
        m_camera = new DefaultCamera(m_cameraNode);
        Render::instance()->setCurrentCamera(m_camera);
}

void FrameWorkTest::initShaders() {
        m_program = new GpuProgram("resources/shaders/lighting");
        Render::instance()->setCurrentProgram(m_program);
}

void FrameWorkTest::init() {
        initRender();
        initEntities();
        initCamera();
        initShaders();
}

void FrameWorkTest::resize(int w, int h) {
        glViewport(0,0, w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void FrameWorkTest::update(float deltaTime) {
        m_camera->update(deltaTime);
        m_camera->node()->rotateInWorld(vec3(0,0,1), 100*deltaTime);
        SHOW(m_camera->node()->localToWorldMatrix());
}

void FrameWorkTest::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Render::instance()->render(m_entityManager->entity("suzanne"));
        Render::instance()->render(m_entityManager->entity("teapot"));
        Render::instance()->render(m_entityManager->entity("cube"));
}
