#include "LightScene.h"
#include "glm/gtx/transform.hpp"
#include "lib/Debug/Debug.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Application.h"

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
        m_program->compileShaderFromFile("shaders/lighting.vert", ShaderType::VERTEX_SHADER);
        m_program->compileShaderFromFile("shaders/lighting.frag", ShaderType::FRAGMENT_SHADER);
        m_program->link();
        m_program->bind();

        m_camera = new Camera();
        m_camera->setPosition(vec3(5,5,5));
        m_camera->setTarget(vec3(0,0,0));

        m_box = new Entity("meshes/cube.obj");
        m_head = new Entity("meshes/model.obj");
        m_head->setPosition(vec3(2,2,1));
        m_box->setPivot(vec3(0.5,0.5,0.5));

        // Установка света
        vec3 lightPosition = vec3(0,0, 30);
        vec3 Ka = vec3(0.1, 0.1, 0.1);
        vec3 La = vec3(1, 1, 1);
        vec3 Kd = vec3(1.0, 1.0, 1.0);
        vec3 Ld = vec3(0.5, 1.0, 1.0);
        vec3 Ks = vec3(1.0, 1.0, 1.0);
        vec3 Ls = vec3(1.0, 1.0, 1.0);
        m_program->setUniform("lightPosition", lightPosition);
        m_program->setUniform("Ka", Ka);
        m_program->setUniform("La", La);
        m_program->setUniform("Kd", Kd);
        m_program->setUniform("Ld", Ld);
        m_program->setUniform("Ks", Ks);
        m_program->setUniform("Ls", Ls);
}

void LightScene::resize(int w, int h) {
        glViewport(0, 0, w, h);
        m_camera->setAspectRatio(float(w)/h);
}

void LightScene::update(float deltaTime) {
        m_head->rotate(vec3(0.1,0.1,0.1));
}

void LightScene::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateMatrix(m_box);
        m_box->vertexArray()->bind();
        glDrawElements(GL_TRIANGLES, m_box->mesh()->indicesCount(), GL_UNSIGNED_INT, (GLvoid *) 0);

        updateMatrix(m_head);
        m_head->vertexArray()->bind();
        glDrawElements(GL_TRIANGLES, m_head->mesh()->indicesCount(), GL_UNSIGNED_INT, (GLvoid *) 0);
}

void LightScene::updateMatrix(Entity *entity) {
        mat4 *projMatrix = m_camera->projectionMatrix();
        mat4 *viewMatrix = m_camera->viewMatrix();
        mat4 *modelMatrix = entity->modelMatrix();

        mat4 modelViewMatrix = *viewMatrix * *modelMatrix;
        mat3 normalMatrix = glm::inverse(glm::transpose(mat3(modelViewMatrix)));
        mat4 mvpMatrix = *projMatrix * modelViewMatrix;

        m_program->setUniform("NormalMatrix", normalMatrix);
        m_program->setUniform("MVPMatrix", mvpMatrix);
        m_program->setUniform("ModelViewMatrix", modelViewMatrix);
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
