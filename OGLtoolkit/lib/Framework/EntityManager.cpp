#include "EntityManager.h"
#include "lib/Utils/Debug.h"

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
        removeAllEntities();
        removeAllMeshes();
}

void EntityManager::addMesh(const Mesh &mesh, const string &meshName) {
        // Создаем VBO, IBO, VAO и загружаем туда данные меша
        MeshInfo* meshInfo = new MeshInfo();
        meshInfo->m_vbo.uploadData(mesh.vertices(), mesh.verticesSize(), Hint::STATIC_DRAW);
        meshInfo->m_ibo.uploadData(mesh.indices(), mesh.indicesSize(), Hint::STATIC_DRAW);

        // Настраиваем VAO (задаем, как должны интерпретировать аттрибуты и т.д
        meshInfo->m_vao.bind();
                meshInfo->m_vbo.setAttribAssociation("vertexPosition", 3, GL_FLOAT, 0, mesh.vertexSize());

                if(mesh.hasNormals()) meshInfo->m_vbo.setAttribAssociation("vertexNormal", 3, GL_FLOAT, mesh.normalOffset(), mesh.vertexSize());
                if(mesh.hasTexCoords()) meshInfo->m_vbo.setAttribAssociation("vertexTexCoord", 2, GL_FLOAT, mesh.texCoordOffset(), mesh.vertexSize());
                if(mesh.hasTangents()) meshInfo->m_vbo.setAttribAssociation("vertexTangent", 3, GL_FLOAT, mesh.tangentOffset(), mesh.vertexSize());

                meshInfo->m_ibo.bind();
        meshInfo->m_vao.unbind();

        // Указываем количество индексов в меше
        meshInfo->m_indicesCount = mesh.indicesCount();

        // Добавляем меш в список доступных
        m_meshes.insert(std::pair<string, MeshInfo*>(meshName, meshInfo));
}

void EntityManager::removeMesh(const string &meshName) {
        MapMeshInfo::iterator it;
        it = m_meshes.find(meshName);

        if(it != m_meshes.end()) {
                delete it->second;
                m_meshes.erase(it);
        } else {
                DEBUG("Error on removing: mesh with name " << meshName << " is not exist");
        }
}

void EntityManager::removeAllMeshes() {
        MapMeshInfo::iterator it;
        for(it = m_meshes.begin(); it != m_meshes.end(); ++it) {
                delete it->second;
        }
        m_meshes.erase(m_meshes.begin(), m_meshes.end());
}

StringList EntityManager::listOfMeshes() const {
        StringList result;

        MapMeshInfo::iterator it;
        for(it = m_meshes.begin(); it != m_meshes.end(); ++it) {
                result.push_back(it->first);
        }

        return result;
}

Entity* EntityManager::createEntity(const string &entityName, const string &meshName) {
        // Ищем меш по имени
        MapMeshInfo::iterator it;
        it = m_meshes.find(meshName);
        if(it == m_meshes.end()) {
                DEBUG("Error on creating entity: mesh with name " << meshName << " is not exist");
                return NULL;
        }

        // Создаем и добавляем новую сущность
        Entity* entity = new Entity(it->second);
        m_entities->insert(std::pair<string, Entity*>(entityName, entity));

        return entity;
}

Entity* EntityManager::entity(const string &entityName) const {
        MapEntity::iterator it;
        it = m_entities.find(entityName);

        if(it != m_entities.end()) {
                return it->second;
        } else {
                DEBUG("Error on finding entity: Entity with name " << entityName << " not found");
                return NULL;
        }
}

void EntityManager::removeEntity(const string &entityName) {
        MapEntity::iterator it;
        it = m_entities.find(entityName);

        if(it != m_entities.end()) {
                delete it->second;
                m_entities.erase(it);
        } else {
                DEBUG("Error on removing entity: Entity with name " << entityName << " not found");
        }
}

void EntityManager::removeAllEntities() {
        MapEntity::iterator it;
        for(it = m_entities.begin(); it != m_entities.end(); ++it) {
                delete it->second;
        }
        m_entities.erase(m_entities.begin(), m_entities.end());
}

StringList EntityManager::listOfEntities() const {
        StringList result;

        MapEntity::iterator it;
        for(it = m_entities.begin(); it != m_entities.end(); ++it) {
                result.push_back(it->first);
        }

        return result;
}
