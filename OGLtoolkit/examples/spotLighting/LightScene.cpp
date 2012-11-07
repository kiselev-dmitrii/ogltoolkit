#include "LightScene.h"
#include "glm/gtx/transform.hpp"
#include "lib/Debug/Debug.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Application.h"
#include "lib/Framework/Render.h"

LightScene::LightScene() {}

LightScene::~LightScene() {
        delete m_program;
        delete m_camera;
        delete m_box;
        delete m_head;
}

void LightScene::init() {
        Mouse::hide();
        glClearColor(0,0,0,0);
        glEnable(GL_DEPTH_TEST);

        //GpuProgram
        m_program = new GpuProgram();
        m_program->compileShaderFromFile("shaders/spotLighting.vert", ShaderType::VERTEX_SHADER);
        m_program->compileShaderFromFile("shaders/spotLighting.frag", ShaderType::FRAGMENT_SHADER);
        m_program->link();
        m_program->bind();
        Render::instance()->setCurrentProgram(m_program);

        m_camera = new Camera();
        m_camera->setPosition(vec3(5,5,5));
        m_camera->setTarget(vec3(0,0,0));
        Render::instance()->setCurrentCamera(m_camera);

        m_box = new Entity("meshes/cube.obj");
        m_head = new Entity("meshes/model.obj");
        m_head->rotate(vec3(90,0,0));
        m_head->setPosition(vec3(0,0,1));
        m_box->setPivot(vec3(0.5,0.5,0.5));
        m_box->setScale(vec3(10,10,0.1));


        // Настройка источника света
        m_program->setUniform("spot.wPosition", vec3(0,0,5));
        m_program->setUniform("spot.wTarget", vec3(0.0));
        m_program->setUniform("spot.cutoff", 30.0f);
        m_program->setUniform("spot.pow", 30.0f);
        m_program->setUniform("spot.ambient", vec3(0.8));
        m_program->setUniform("spot.diffuse", vec3(0.8,0.8,1.0));
        m_program->setUniform("spot.specular", vec3(1.0));

        // Установка материала по дефолту
        m_program->setUniform("material.ambient", vec3(0.1));
        m_program->setUniform("material.specular", vec3(1.0));
        m_program->setUniform("material.shininess", 80.0f);
}

void LightScene::resize(int w, int h) {
        glViewport(0, 0, w, h);
        m_camera->setAspectRatio(float(w)/h);
}

void LightScene::update(float deltaTime) {
        //m_head->rotate(deltaTime*vec3(0,100,0));
        //SHOW(1.0/deltaTime);
}

void LightScene::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_program->setUniform("material.ambient", vec3(0.1));
        m_program->setUniform("material.diffuse", vec3(0.3,0.3,0.3));
        Render::instance()->render(m_box);

        m_program->setUniform("material.ambient", vec3(0.2, 0.3, 0.3));
        m_program->setUniform("material.diffuse",vec3(0.5, 1.0, 1.0));
        Render::instance()->render(m_head);
}

void LightScene::onMouseMove(int x, int y) {
        ivec2 pos = ivec2(x,y);
        Mouse::setPos(Application::instance()->window()->center());
        vec2 delta = vec2(Application::instance()->window()->center() - pos);
        m_camera->rotateWithMouse(delta);
}

void LightScene::onKeyPress(int key) {
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
