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

        m_entityManager = new EntityManager();
        m_entityManager->addMesh(Mesh("resources/meshes/cube.obj"), "cube.mesh");

        m_entityManager->createEntity("cube", "cube.mesh");

        m_entityManager->entity("cube")->setNode(m_node1);
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
}

void FrameWorkTest::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Render::instance()->render(m_entityManager->entity("cube"));
}
