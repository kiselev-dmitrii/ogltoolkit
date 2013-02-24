#include "Render.h"
#include "lib/Utils/Debug.h"

Render* Render::instance() {
        static Render instance;
        return &instance;
}

void Render::setCurrentProgram(GpuProgram *program) {
        m_curProgram = program;
        program->bind();
}

GpuProgram* Render::currentProgram() {
        return m_curProgram;
}

void Render::setCurrentCamera(Camera *camera) {
        m_curCamera = camera;
}

Camera* Render::currentCamera() {
        return m_curCamera;
}

void Render::updateMatrices(Camera *camera, Entity *entity) {
        mat4 *projMatrix = camera->projectionMatrix();
        mat4 *viewMatrix = camera->viewMatrix();
        mat4 *modelMatrix = entity->modelMatrix();

        mat4 modelViewMatrix = *viewMatrix * *modelMatrix;
        mat3 normalMatrix =  glm::inverse(glm::transpose(mat3(modelViewMatrix)));
        mat4 mvpMatrix = *projMatrix * modelViewMatrix;

        m_curProgram->setUniform("V", *viewMatrix);
        m_curProgram->setUniform("M", *modelMatrix);
        m_curProgram->setUniform("MV", modelViewMatrix);
        m_curProgram->setUniform("MVP", mvpMatrix);
        m_curProgram->setUniform("N", normalMatrix);
}

void Render::render(Entity *entity) {
        updateMatrices(m_curCamera, entity);
        entity->vertexArray()->bind();
        glDrawElements(GL_TRIANGLES, entity->mesh()->indicesCount(), GL_UNSIGNED_INT, (GLvoid *) 0);
}
