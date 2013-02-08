#include "FBOTestScene.h"
#include "lib/Framework/Render.h"
#include "lib/Subsystems/Application.h"
#include "lib/Subsystems/Mouse.h"

FBOTestScene::FBOTestScene() { }

FBOTestScene::~FBOTestScene() {
}

void FBOTestScene::init() {
        initRender();
        initTeapot();
        initBox();

        renderToTexture();
}

void FBOTestScene::resize(int w, int h) {
        glViewport(0,0,w,h);
        m_camera->setAspectRatio(float(w)/h);
}

void FBOTestScene::update(float deltaTime) {
}

void FBOTestScene::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderBox();
        renderTeapot();
}

void FBOTestScene::onKeyPress(int key) {
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

void FBOTestScene::onMouseMove(int x, int y) {
        Mouse::hide();

        ivec2 pos = ivec2(x,y);
        Mouse::setPos(Application::instance()->window()->center());
        vec2 delta = vec2(Application::instance()->window()->center() - pos);
        m_camera->rotateWithMouse(delta);
}

void FBOTestScene::initRender() {
        glClearColor(0.9, 0.9, 0.9, 1.0);
        glEnable(GL_DEPTH_TEST);

        m_lightingProgram = new GpuProgram("resources/shaders/lighting");
        Render::instance()->setCurrentProgram(m_lightingProgram);

        m_camera = new Camera();
        Render::instance()->setCurrentCamera(m_camera);

        m_lightingProgram->setUniform("lightPosition", vec3(10,10,100));
        m_lightingProgram->setUniform("Ld", vec3(1.0, 1.0, 0.9));
        m_lightingProgram->setUniform("La", vec3(0.3, 0.3, 0.3));
        m_lightingProgram->setUniform("Ls", vec3(1.0, 1.0, 1.0));

        m_tuBoxCover = new TextureUnit;
        m_brickTexture = new Texture2D("resources/images/brick1.jpg");

}

void FBOTestScene::initTeapot() {
        m_eTeapot = new Entity(Mesh("resources/meshes/teapot.obj", 1));
        m_eTeapot->setOrientation(vec3(90,90,0));
        m_eTeapot->setScale(vec3(0.5,0.5,0.5));
}

void FBOTestScene::initBox() {
        m_eBox = new Entity("resources/meshes/cube.obj");
        m_eBox->setPosition(vec3(10, 10, 0));
}

void FBOTestScene::renderBox() {
        m_tuBoxCover->bind();
        m_tColorBuff->bind();
        //m_brickTexture->bind();

        m_lightingProgram->setUniform("Kd", vec3(1.0,0.2,1.0));
        m_lightingProgram->setUniform("Ka", vec3(0.3,0.3,0.3));
        m_lightingProgram->setUniform("Ks", vec3(1.0,1.0,1.0));
        m_lightingProgram->setUniform("isDrawBox", true);
        m_lightingProgram->setUniform("texture", m_tuBoxCover->number());

        Render::instance()->render(m_eBox);
}

void FBOTestScene::renderTeapot() {
        m_lightingProgram->setUniform("Kd", vec3(1.0,0.5,0.2));
        m_lightingProgram->setUniform("Ka", vec3(0.3,0.3,0.3));
        m_lightingProgram->setUniform("Ks", vec3(1.0,1.0,1.0));
        m_lightingProgram->setUniform("isDrawBox", false);

        Render::instance()->render(m_eTeapot);
}

void FBOTestScene::renderTeapotFromView() {
        Camera tmpCamera = Camera();
        tmpCamera.setPosition(vec3(4,4,4));
        tmpCamera.setTarget(vec3(0,0,2));

        Render::instance()->setCurrentCamera(&tmpCamera);
        renderTeapot();
        Render::instance()->setCurrentCamera(m_camera);
}

void FBOTestScene::renderToTexture() {
        //Рендерим в текстуру чайник
        //Создаем текстуру и рендербуфер
        m_tColorBuff = new Texture2D(512, 512);
        m_rbDepthBuff = new Renderbuffer(512, 512, RenderbufferFormat::DEPTH_16);

        m_fbo = new Framebuffer();
        m_fbo->attachAsColorBuffer(*m_tColorBuff);
        m_fbo->attachAsDepthBuffer(*m_rbDepthBuff);
        m_fbo->bind();
        GLenum drawBufs[] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, drawBufs);
        glViewport(0, 0, 512, 512);
        renderTeapotFromView();
        m_fbo->unbind();
}
