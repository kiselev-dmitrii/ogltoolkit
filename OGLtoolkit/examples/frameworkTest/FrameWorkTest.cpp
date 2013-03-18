#include "FrameWorkTest.h"
#include "lib/Utils/Debug.h"
#include "lib/Subsystems/Keyboard.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Application.h"


FrameWorkTest::FrameWorkTest() {
        m_entityMgr = EntityManager::instance();
        m_renderMgr = RenderManager::instance();
        m_meshMgr = MeshManager::instance();
}

FrameWorkTest::~FrameWorkTest() {
}

void FrameWorkTest::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        Mouse::hide();
}

void FrameWorkTest::initEntities() {
        m_node1 = new SceneNode("Node1");
        m_node2 = new SceneNode("Node2");
        m_node3 = new SceneNode("Node3");

        m_node2->setParentNode(m_node1);
        m_node2->setPositionInParent(vec3(10,10,0));
        m_node3->setParentNode(m_node2);
        m_node3->setPositionInParent(vec3(-4,-4,0));

        m_meshMgr->loadMesh("sphere.mesh", "resources/meshes/sphere.obj");
        m_meshMgr->loadMesh("cube.mesh", "resources/meshes/cube.obj");
        m_meshMgr->loadMesh("pyramid.mesh", "resources/meshes/pyramid.obj");
        m_meshMgr->loadMesh("bullet1.mesh", "resources/meshes/bullet.3ds", 0);
        m_meshMgr->loadMesh("bullet2.mesh", "resources/meshes/bullet.3ds", 1);

        m_entityMgr->createEntity("earth", "sphere.mesh");
        m_entityMgr->createEntity("moon", "pyramid.mesh");
        m_entityMgr->createEntity("bullet1", "bullet1.mesh")->setNode(m_node1);
        m_entityMgr->createEntity("bullet2", "bullet2.mesh")->setNode(m_node1);

        m_entityMgr->entity("earth")->setNode(m_node2);
        m_entityMgr->entity("moon")->setNode(m_node3);
}

void FrameWorkTest::initCamera() {
        m_cameraNode1 = new SceneNode("Camera_node1");
        m_cameraNode2 = new SceneNode("Camera_node2");
        m_camera = new FirstPersonCamera(m_cameraNode1);
        m_cameraNode1->setParentNode(m_node3);
        m_renderMgr->setCurrentCamera(m_camera);
}

void FrameWorkTest::initShaders() {
        m_renderMgr->addProgram("lighting", new GpuProgram("resources/shaders/lighting"));
        m_renderMgr->setCurrentProgram("lighting");

        m_renderMgr->currentProgram()->setUniform("light.position", vec3(10));
        m_renderMgr->currentProgram()->setUniform("light.color", vec3(1));
}

void FrameWorkTest::init() {
        initRender();
        initShaders();
        initEntities();
        initCamera();
}

void FrameWorkTest::resize(int w, int h) {
        glViewport(0,0, w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void FrameWorkTest::update(float deltaTime) {
        m_camera->update(deltaTime);
        SHOW(1.0/deltaTime);

        m_node1->rotateInParent(vec3(1,1,1), 40*deltaTime);
        m_node2->rotateInParent(vec3(0,1,1), 50*deltaTime);
        m_node3->rotateInParent(vec3(0,0,1), 60*deltaTime);

        if(Keyboard::isKeyPressed('1')) m_camera->setNode(m_cameraNode1);
        if(Keyboard::isKeyPressed('2')) m_camera->setNode(m_cameraNode2);
}

void FrameWorkTest::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_renderMgr->currentProgram()->setUniform("material.ambient", vec3(0.3));
        m_renderMgr->currentProgram()->setUniform("material.diffuse", vec3(1, 1, 0));
        m_renderMgr->currentProgram()->setUniform("material.specular", vec3(1.0));
        m_renderMgr->currentProgram()->setUniform("material.shininess", 80.0f);
        m_renderMgr->render(m_entityMgr->entities());
}
