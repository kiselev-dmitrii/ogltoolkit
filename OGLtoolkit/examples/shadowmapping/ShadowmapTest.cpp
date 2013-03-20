#include "ShadowmapTest.h"
#include "lib/Utils/Debug.h"
#include "lib/Subsystems/Keyboard.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Application.h"
#include "lib/Solutions/FirstPersonCamera.h"


ShadowmapTest::ShadowmapTest() {
        m_entityMgr = EntityManager::instance();
        m_renderMgr = RenderManager::instance();
        m_meshMgr = MeshManager::instance();
        m_sceneMgr = SceneManager::instance();
}

ShadowmapTest::~ShadowmapTest() {
}

void ShadowmapTest::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        Mouse::hide();
}

void ShadowmapTest::initEntities() {
        m_node1 = m_sceneMgr->rootNode()->createChildNode("Node1");
        m_node2 = m_sceneMgr->rootNode()->createChildNode("Node2");
        m_node3 = m_node2->createChildNode("Node3");
        m_node4 = m_node3->createChildNode("Node4");

        m_node2->setPositionInParent(vec3(4,0,0));

        m_meshMgr->loadMesh("teapot.mesh", "resources/meshes/teapot.obj", 1);
        m_meshMgr->loadMesh("cube.mesh", "resources/meshes/cube.obj");

        m_entityMgr->createEntity("plane", "cube.mesh")->setNode(m_node1);
        m_node1->setScaleInParent(vec3(100,100,0.1));
        m_entityMgr->createEntity("teapot", "teapot.mesh")->setNode(m_node2);
        m_node2->rotateInLocal(vec3(1,0,0), 90);

        m_entityMgr->createEntity("microteapot", "teapot.mesh")->setNode(m_node4);
        m_node4->setScaleInParent(vec3(0.1, 0.1, 0.1));
        m_node4->setPositionInParent(vec3(5,5,5));
}

void ShadowmapTest::initCamera() {
        SceneNode* cameraNode = m_sceneMgr->rootNode()->createChildNode("Camera_Node");
        AbstractCamera* camera = m_sceneMgr->addCamera("Camera1", new FirstPersonCamera(cameraNode));
        m_sceneMgr->setCurrentCamera(camera);
}

void ShadowmapTest::initShaders() {
        StringList defines; defines.push_back("PHONG_LIGHT_MODEL");
        m_renderMgr->addProgram("phongLighting", new GpuProgram("resources/shaders/ubershader", defines));
        m_renderMgr->setCurrentProgram("phongLighting");

        m_renderMgr->currentProgram()->setUniform("light.position", vec3(10));
        m_renderMgr->currentProgram()->setUniform("light.color", vec3(1));
}

void ShadowmapTest::init() {
        initRender();
        initShaders();
        initEntities();
        initCamera();
}

void ShadowmapTest::resize(int w, int h) {
        glViewport(0,0, w,h);
        m_sceneMgr->currentCamera()->setAspectRatio(float(w)/h);
}

void ShadowmapTest::update(float deltaTime) {
        m_sceneMgr->currentCamera()->update(deltaTime);

        //SHOW(Application::fps());

        m_node4->rotateInWorld(vec3(0,0,1), 60*deltaTime);
        m_node3->rotateInWorld(vec3(0,0,1), -40*deltaTime);
}

void ShadowmapTest::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_renderMgr->currentProgram()->setUniform("material.ambient", vec3(0.3));
        m_renderMgr->currentProgram()->setUniform("material.diffuse", vec3(1, 1, 0));
        m_renderMgr->currentProgram()->setUniform("material.specular", vec3(1.0));
        m_renderMgr->currentProgram()->setUniform("material.shininess", 80.0f);
        m_renderMgr->render(m_entityMgr->entities());
}
