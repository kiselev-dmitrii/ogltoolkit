#include "FrameWorkTest.h"
#include "lib/Framework/Render.h"
#include "lib/Utils/Debug.h"
#include "lib/Subsystems/Keyboard.h"

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
        m_entityManager->addMesh(Mesh("resources/meshes/sphere.obj"), "sphere.mesh");
        m_entityManager->addMesh(Mesh("resources/meshes/cube.obj"), "cube.mesh");
        m_entityManager->addMesh(Mesh("resources/meshes/pyramid.obj"), "pyramid.mesh");
        m_entityManager->addMesh(Mesh("resources/meshes/bullet.3ds", 0), "bullet1.mesh");
        m_entityManager->addMesh(Mesh("resources/meshes/bullet.3ds", 1), "bullet2.mesh");

        m_entityManager->createEntity("earth", "sphere.mesh");
        m_entityManager->createEntity("moon", "sphere.mesh");
        m_entityManager->createEntity("bullet1", "bullet1.mesh")->setNode(m_node1);
        m_entityManager->createEntity("bullet2", "bullet2.mesh")->setNode(m_node1);

        m_entityManager->entity("earth")->setNode(m_node2);
        m_entityManager->entity("moon")->setNode(m_node3);
}

void FrameWorkTest::initCamera() {
        m_cameraNode1 = new SceneNode("Camera_node1");
        m_cameraNode2 = new SceneNode("Camera_node2");
        m_camera = new FirstPersonCamera(m_cameraNode1);
        m_cameraNode1->setParentNode(m_node3);

        Render::instance()->setCurrentCamera(m_camera);
        m_entityManager->createEntity("cam1_pyramid", "cube.mesh")->setNode(m_cameraNode1);
        m_entityManager->createEntity("cam2_pyramid", "cube.mesh")->setNode(m_cameraNode2);
}

void FrameWorkTest::initShaders() {
        m_program = new GpuProgram("resources/shaders/lighting");
        Render::instance()->setCurrentProgram(m_program);

        m_program->setUniform("light.position", vec3(10));
        m_program->setUniform("light.color", vec3(1));
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

        m_node1->rotateInParent(vec3(1,1,1), 40*deltaTime);
        m_node2->rotateInParent(vec3(0,1,1), 50*deltaTime);
        m_node3->rotateInParent(vec3(0,0,1), 60*deltaTime);

        if(Keyboard::isKeyPressed('1')) m_camera->setNode(m_cameraNode1);
        if(Keyboard::isKeyPressed('2')) m_camera->setNode(m_cameraNode2);
}

void FrameWorkTest::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_program->setUniform("material.ambient", vec3(0.3));
        m_program->setUniform("material.diffuse", vec3(1, 1, 0));
        m_program->setUniform("material.specular", vec3(1.0));
        m_program->setUniform("material.shininess", 80.0f);
        Render::instance()->render(m_entityManager->entity("bullet1"));
        Render::instance()->render(m_entityManager->entity("bullet2"));
        m_program->setUniform("material.ambient", vec3(0.3));
        m_program->setUniform("material.diffuse", vec3(0, 0, 1));
        m_program->setUniform("material.specular", vec3(1.0));
        m_program->setUniform("material.shininess", 80.0f);
        Render::instance()->render(m_entityManager->entity("earth"));
        m_program->setUniform("material.ambient", vec3(0.3));
        m_program->setUniform("material.diffuse", vec3(0.5, 0.5, 0.5));
        m_program->setUniform("material.specular", vec3(1.0));
        m_program->setUniform("material.shininess", 80.0f);
        Render::instance()->render(m_entityManager->entity("moon"));

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        Render::instance()->render(m_entityManager->entity("cam1_pyramid"));
        Render::instance()->render(m_entityManager->entity("cam2_pyramid"));
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
