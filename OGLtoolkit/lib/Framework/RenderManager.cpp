#include "RenderManager.h"
#include "MeshInfo.h"
#include "Entity.h"
#include "EntityManager.h"
#include "AbstractCamera.h"
#include "lib/Subsystems/Application.h"
#include "lib/Utils/Debug.h"

RenderManager::RenderManager() {
}

RenderManager* RenderManager::instance() {
        static RenderManager instance;
        return &instance;
}

RenderManager::~RenderManager() {
}

void RenderManager::addProgram(const string &programName, const GpuProgram *program) {
        m_programs.insert(std::pair<string, GpuProgram*>(programName, program));
}

void RenderManager::removeProgram(const string &programName) {
        MapGpuProgram::iterator it;
        it = m_programs.find(programName);

        if(it != m_programs.end()) {
                delete it->second;
                m_programs.erase(it);
        } else {
                DEBUG("Error on removing: program with name " << programName << " is not exist");
        }
}

void RenderManager::removeAllProgram() {
        MapGpuProgram::iterator it;
        for(it = m_programs.begin(); it != m_programs.end(); ++it) {
                delete it->second;
        }
        m_programs.erase(m_programs.begin(), m_programs.end());
}

GpuProgram* RenderManager::program(const string &programName) const {
        MapGpuProgram::const_iterator it;
        it = m_programs.find(programName);

        if(it != m_programs.end()) {
                return it->second;
        } else {
                DEBUG("Error on finding: program with name " << programName << " not found");
                return NULL;
        }
}

void RenderManager::setCurrentProgram(const string &programName) {
        GpuProgram* gpuProgram = program(programName);
        if(gpuProgram) {
                m_currentProgram = gpuProgram;
                m_uniformSupplier.calculateFlags(m_currentProgram);
        }
}

GpuProgram* RenderManager::currentProgram() {
        return m_currentProgram;
}

void RenderManager::setCurrentCamera(AbstractCamera *camera) {
        m_currentCamera = camera;
}

AbstractCamera* RenderManager::currentCamera() const {
        return m_currentCamera;
}


void RenderManager::render(Entity *entity) {
        uploadUniforms(entity);

        entity->meshInfo()->vertexArray()->bind();
        glDrawElements(GL_TRIANGLES, entity->meshInfo()->indicesCount(), GL_UNSIGNED_INT, (GLvoid *) 0);
}

void RenderManager::render(MapEntity *entities) {
        MapEntity::iterator it;
        for(it = entities->begin(); it != entities->end(); ++it) {
                //Нужно использовать материал
                //it->second->material()->bind();

                render(it->second);
        }
}

void RenderManager::uploadUniforms(Entity *entity) {
        // Обычно MV и MVP матрицы нужны всегда
        mat4 P = m_currentCamera->viewToScreenMatrix();
        mat4 V = m_currentCamera->node()->worldToLocalMatrix();
        mat4 M = entity->node()->localToWorldMatrix();
        mat4 MV = V*M;
        mat4 MVP = P*MV;

        if(m_uniformSupplier.isNeedSupplyUniform(AutoUniforms::ViewMatrix)) {
                m_currentProgram->setUniform(UniformSupplier::ViewMatrixName, V);
        }
        if(m_uniformSupplier.isNeedSupplyUniform(AutoUniforms::InverseViewMatrix)) {
                m_currentProgram->setUniform(UniformSupplier::InverseViewMatrixName, m_currentCamera->node()->localToWorldMatrix());
        }
        if(m_uniformSupplier.isNeedSupplyUniform(AutoUniforms::ModelMatrix)) {
                m_currentProgram->setUniform(UniformSupplier::ModelMatrixName, M);
        }
        if(m_uniformSupplier.isNeedSupplyUniform(AutoUniforms::NormalMatrix)) {
                mat3 N =  glm::inverse(glm::transpose(mat3(MV)));
                m_currentProgram->setUniform(UniformSupplier::NormalMatrixName, N);
        }
        if(m_uniformSupplier.isNeedSupplyUniform(AutoUniforms::ModelViewMatrix)) {
                m_currentProgram->setUniform(UniformSupplier::ModelViewMatrixName, MV);
        }
        if(m_uniformSupplier.isNeedSupplyUniform(AutoUniforms::ModelViewProjectionMatrix)) {
                m_currentProgram->setUniform(UniformSupplier::ModelViewProjectionMatrixName, MVP);
        }

        if(m_uniformSupplier.isNeedSupplyUniform(AutoUniforms::TimeValue)) {
                m_currentProgram->setUniform(UniformSupplier::TimeValueName, Application::executionTime());
        }
        if(m_uniformSupplier.isNeedSupplyUniform(AutoUniforms::WindowSize)) {
                m_currentProgram->setUniform(UniformSupplier::WindowSizeName, vec2(Application::window()->size()));
        }
}
