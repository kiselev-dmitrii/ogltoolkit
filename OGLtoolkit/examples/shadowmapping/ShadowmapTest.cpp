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
        m_texMgr = TextureManager::instance();
}

ShadowmapTest::~ShadowmapTest() {
}

void ShadowmapTest::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        Mouse::hide();
}

void ShadowmapTest::initEntities() {
        m_node1 = m_sceneMgr->rootNode()->createChildNode("Node1");
        m_node2 = m_sceneMgr->rootNode()->createChildNode("Node2");
        m_node3 = m_node2->createChildNode("Node3");
        m_node4 = m_node3->createChildNode("Node4");


        m_meshMgr->loadMesh("teapot.mesh", "resources/meshes/teapot.obj", 1);
        m_meshMgr->loadMesh("cube.mesh", "resources/meshes/cube.obj");
        m_meshMgr->loadMesh("_quad.mesh", Mesh::createQuad());
        m_quad = m_meshMgr->mesh("_quad.mesh");

        m_entityMgr->createEntity("plane", "cube.mesh")->setNode(m_node1);

        SceneNode* node = m_sceneMgr->rootNode()->createChildNode("wall1");
        m_entityMgr->createEntity("wall1", "cube.mesh")->setNode(node);
        node->setScaleInParent(vec3(0.1,100,100));

        node = m_sceneMgr->rootNode()->createChildNode("wall2");
        m_entityMgr->createEntity("wall2", "cube.mesh")->setNode(node);
        node->setScaleInParent(vec3(100,0.1,100));


        m_node1->setScaleInParent(vec3(100,100,0.1));
        m_entityMgr->createEntity("teapot", "teapot.mesh")->setNode(m_node2);
        m_node2->rotateInLocal(vec3(1,0,0), 90);
        m_node2->setPositionInParent(vec3(8,8,0));

        m_entityMgr->createEntity("microteapot", "teapot.mesh")->setNode(m_node4);
        m_node4->setScaleInParent(vec3(0.1, 0.1, 0.1));
        m_node4->setPositionInParent(vec3(5,5,5));
}

void ShadowmapTest::initCamera() {
        SceneNode* cameraNode = m_sceneMgr->rootNode()->createChildNode("Camera_Node");
        m_mainCamera = (FirstPersonCamera*)m_sceneMgr->addCamera("mainCamera", new FirstPersonCamera(cameraNode));
        m_sceneMgr->setCurrentCamera(m_mainCamera);
        m_mainCamera->node()->setPositionInWorld(vec3(30,30,30));
        m_mainCamera->node()->lookAt(vec3(8,8,0), vec3(0,0,1));
}

void ShadowmapTest::initShaders() {
        m_tu = new TextureUnit();

        StringList defines1; defines1.push_back("RECORD_DEPTH");
        m_renderMgr->addProgram("recordDepth", new GpuProgram("resources/shaders/ubershader", defines1));
        StringList defines2; defines2.push_back("PHONG_LIGHT_MODEL");
        m_renderMgr->addProgram("phongLighting", new GpuProgram("resources/shaders/ubershader", defines2));

        m_renderMgr->setCurrentProgram("phongLighting");

        m_renderMgr->currentProgram()->setUniform("light.position", m_spot->node()->positionInWorld());
        m_renderMgr->currentProgram()->setUniform("light.color", m_spot->diffuseColor());
        m_renderMgr->currentProgram()->setUniform("material.ambient", vec3(0.3));
        m_renderMgr->currentProgram()->setUniform("material.diffuse", vec3(1, 1, 0));
        m_renderMgr->currentProgram()->setUniform("material.specular", vec3(1.0));
        m_renderMgr->currentProgram()->setUniform("material.shininess", 80.0f);
}

void ShadowmapTest::initFBO() {
        ColorTexture2D* color = m_texMgr->addColorTexture2D("_colorBuf.tex", new ColorTexture2D(Application::window()->size()));
        DepthTexture2D* depth = m_texMgr->addDepthTexture2D("_depthBuf.tex", new DepthTexture2D(Application::window()->size()));

        m_fbo = new Framebuffer();
        m_fbo->attachAsColorBuffer(color);
        m_fbo->attachAsDepthBuffer(depth);

        m_tu->bindTexture(depth);
}

void ShadowmapTest::initLight() {
        SceneNode* node = m_sceneMgr->rootNode()->createChildNode("spotNode");
        node->setPositionInWorld(vec3(30));
        m_sceneMgr->addCamera("spotCamera", new FirstPersonCamera(node));

        m_spot = new Spotlight(node);
        m_spot->bindCamera(m_sceneMgr->camera("spotCamera"));

}

void ShadowmapTest::init() {
        initRender();
        initLight();
        initShaders();
        initEntities();
        initCamera();
        initFBO();
}

void ShadowmapTest::resize(int w, int h) {
        glViewport(0,0, w,h);
        m_sceneMgr->currentCamera()->setAspectRatio(float(w)/h);
}

void ShadowmapTest::update(float deltaTime) {
        m_sceneMgr->currentCamera()->update(deltaTime);

        static float remainTime = 1.0;
        if (remainTime <= 0.0) {
                SHOW(Application::fps());
                remainTime = 1.0;
        }

        else remainTime -= deltaTime;

        m_node4->rotateInWorld(vec3(0,0,1), 60*deltaTime);
        m_node3->rotateInWorld(vec3(0,0,1), -40*deltaTime);
}

void ShadowmapTest::pass1() {
        m_renderMgr->setCurrentProgram("recordDepth");
        m_sceneMgr->setCurrentCamera(m_spot->camera());

        m_fbo->bind();
                glCullFace(GL_FRONT);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                m_renderMgr->render(m_entityMgr->entities());
        m_fbo->unbind();
}

void ShadowmapTest::pass2() {
        m_sceneMgr->setCurrentCamera(m_mainCamera);
        m_renderMgr->setCurrentProgram("phongLighting");
        glCullFace(GL_BACK);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_renderMgr->render(m_entityMgr->entities());
}

void ShadowmapTest::render() {
        pass1();
        pass2();
}
