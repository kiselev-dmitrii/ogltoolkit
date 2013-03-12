#include "Render.h"
#include "lib/Utils/Debug.h"
#include "EntityManager.h"

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

void Render::setCurrentCamera(AbstractCamera *camera) {
        m_curCamera = camera;
}

AbstractCamera* Render::currentCamera() {
        return m_curCamera;
}

void Render::updateMatrices(AbstractCamera *camera, Entity *entity) {
        mat4 projMatrix = camera->viewToScreenMatrix();
        mat4 viewMatrix = camera->node()->worldToLocalMatrix();
        mat4 modelMatrix = entity->node()->localToWorldMatrix();

        mat4 modelViewMatrix = viewMatrix * modelMatrix;
        mat3 normalMatrix =  glm::inverse(glm::transpose(mat3(modelViewMatrix)));
        mat4 mvpMatrix = projMatrix * modelViewMatrix;

        m_curProgram->setUniform("V", viewMatrix);
        m_curProgram->setUniform("M", modelMatrix);
        m_curProgram->setUniform("MV", modelViewMatrix);
        m_curProgram->setUniform("MVP", mvpMatrix);
        m_curProgram->setUniform("N", normalMatrix);
}

void Render::render(Entity *entity) {
        updateMatrices(m_curCamera, entity);
        entity->meshInfo()->m_vao.bind();
        glDrawElements(GL_TRIANGLES, entity->meshInfo()->m_indicesCount, GL_UNSIGNED_INT, (GLvoid *) 0);
}
