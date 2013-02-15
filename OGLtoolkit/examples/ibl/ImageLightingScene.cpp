#include "ImageLightingScene.h"
#include "lib/Framework/Render.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Application.h"

ImageLightingScene::ImageLightingScene() { }

ImageLightingScene::~ImageLightingScene() {
}

void ImageLightingScene::init() {
        Mouse::hide();

        initRender();

        initSkybox();
        initTeapot();
}

void ImageLightingScene::resize(int w, int h) {
        glViewport(0,0,w,h);
        m_camera->setAspectRatio(float(w)/h);
        m_camera->setFarClipDistance(500);
}

void ImageLightingScene::update(float deltaTime) {
}

void ImageLightingScene::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderSkybox();
        renderTeapot();
}

void ImageLightingScene::onKeyPress(int key) {
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

void ImageLightingScene::onMouseMove(int x, int y) {
        ivec2 pos = ivec2(x,y);
        Mouse::setPos(Application::instance()->window()->center());
        vec2 delta = vec2(Application::instance()->window()->center() - pos);
        m_camera->rotateWithMouse(delta);
}

void ImageLightingScene::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        m_iblLighting = new GpuProgram("resources/shaders/iblLighting");
        m_renderCubemap = new GpuProgram("resources/shaders/renderCubemap");

        m_camera = new Camera();

        m_tcRoom = new TextureCube("resources/images/room", "jpg");
        m_tcDiffuseRoom = new TextureCube("resources/images/room_diffuse", "jpg");
        m_tcSpecularRoom = new TextureCube("resources/images/room_specular", "jpg");

        m_tuBase = new TextureUnit();
        m_tuBase->bindTexture(*m_tcRoom);
        m_tuDiffuse = new TextureUnit();
        m_tuDiffuse->bindTexture(*m_tcDiffuseRoom);
        m_tuSpecular = new TextureUnit();
        m_tuSpecular->bindTexture(*m_tcSpecularRoom);

        Render::instance()->setCurrentCamera(m_camera);
        //Render::instance()->setCurrentProgram(m_renderCubemap);
        Render::instance()->setCurrentProgram(m_iblLighting);
}

void ImageLightingScene::initTeapot() {
        m_eTeapot = new Entity(Mesh("resources/meshes/suzanne.obj", 0, MeshFlags::NORMALS | MeshFlags::TEXCOORDS));
        m_eTeapot->setOrientation(vec3(90,90,0));
}

void ImageLightingScene::initSkybox() {
        m_eSkybox = new Entity(Mesh("resources/meshes/cube.obj", 0, MeshFlags::NORMALS | MeshFlags::TEXCOORDS));
        m_eSkybox->setScale(vec3(100,100,100));
}

void ImageLightingScene::renderSkybox() {
        Render::instance()->setCurrentProgram(m_renderCubemap);
        m_renderCubemap->setUniform("cubemap", m_tuBase->number());
        Render::instance()->render(m_eSkybox);
}

void ImageLightingScene::renderTeapot() {
        Render::instance()->setCurrentProgram(m_iblLighting);
        m_iblLighting->setUniform("wCameraPosition", m_camera->position());

        m_iblLighting->setUniform("base", m_tuBase->number());
        m_iblLighting->setUniform("diffusemap", m_tuDiffuse->number());
        m_iblLighting->setUniform("specularmap", m_tuSpecular->number());

        m_iblLighting->setUniform("material.baseColor", vec3(0.2));
        m_iblLighting->setUniform("material.diffuseFactor", 1.0f);
        m_iblLighting->setUniform("material.specularFactor", 1.0f);


        Render::instance()->render(m_eTeapot);
}
