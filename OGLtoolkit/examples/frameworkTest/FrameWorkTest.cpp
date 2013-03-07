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

        m_node2->setParentNode(m_node1);
        m_node2->setPositionInParent(vec3(10,10,0));
        m_node3->setParentNode(m_node2);
        m_node3->setPositionInParent(vec3(-4,-4,0));

        m_entityManager = new EntityManager();
        m_entityManager->addMesh(Mesh("resources/meshes/cube.obj"), "cube.mesh");
        m_entityManager->addMesh(Mesh("resources/meshes/suzanne.obj"), "suzanne.mesh");
        m_entityManager->addMesh(Mesh("resources/meshes/teapot.obj", 1), "teapot.mesh");

        m_entityManager->createEntity("cube", "cube.mesh");
        m_entityManager->createEntity("suzanne", "suzanne.mesh");
        m_entityManager->createEntity("teapot", "teapot.mesh");

        m_entityManager->entity("teapot")->setNode(m_node1);
        m_entityManager->entity("cube")->setNode(m_node2);
        m_entityManager->entity("suzanne")->setNode(m_node3);
}

void FrameWorkTest::initCamera() {
        m_cameraNode = new SceneNode("Camera_node");
        m_camera = new DefaultCamera(m_cameraNode);
        Render::instance()->setCurrentCamera(m_camera);
}

void FrameWorkTest::initShaders() {
        m_program = new GpuProgram("resources/shaders/lighting");
        Render::instance()->setCurrentProgram(m_program);

        m_program->setUniform("light.position", vec3(10));
        m_program->setUniform("light.color", vec3(1));

        m_program->setUniform("material.ambient", vec3(0.3));
        m_program->setUniform("material.diffuse", vec3(1, 0, 0));
        m_program->setUniform("material.specular", vec3(1.0));
        m_program->setUniform("material.shininess", 80.0f);
}

void FrameWorkTest::init() {
        initRender();
        initCamera();
        initShaders();
        initEntities();
}

void FrameWorkTest::resize(int w, int h) {
        glViewport(0,0, w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void FrameWorkTest::update(float deltaTime) {
        SHOW(1.0/deltaTime);
        m_camera->update(deltaTime);

        m_node1->rotateInParent(vec3(1,1,1), 40*deltaTime);
        m_node2->rotateInParent(vec3(0,1,1), 50*deltaTime);
        m_node3->rotateInParent(vec3(0,0,1), 60*deltaTime);
}

void FrameWorkTest::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Render::instance()->render(m_entityManager->entity("cube"));
        Render::instance()->render(m_entityManager->entity("suzanne"));
        Render::instance()->render(m_entityManager->entity("teapot"));
}
