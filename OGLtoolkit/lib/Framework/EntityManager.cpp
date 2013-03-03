#include "EntityManager.h"
#include "lib/Utils/Debug.h"

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
        // Удаляем все cущности и буферы
        MapEntity::iterator it;
        for(it = m_entities.begin(); it != m_entities.end(); ++it) {
                delete it->second;
        }

        MapTriple::iterator it;
        for(it = m_triples.begin(); it != m_triples.end(); ++it) {
                delete it->second;
        }
}

void EntityManager::addMesh(const Mesh &mesh, const string &meshName) {
        // Создаем VBO, IBO, VAO и загружаем туда данные меша
        Triple* triple = new Triple();
        triple->m_vbo.uploadData(mesh.vertices(), mesh.verticesSize(), Hint::STATIC_DRAW);
        triple->m_ibo.uploadData(mesh.indices(), mesh.indicesSize(), Hint::STATIC_DRAW);

        // Настраиваем VAO (задаем, как должны интерпретировать аттрибуты и т.д
        triple->m_vao.bind();
                triple->m_vbo.setAttribAssociation("vertexPosition", 3, GL_FLOAT, 0, mesh.vertexSize());

                if(mesh.hasNormals()) triple->m_vbo.setAttribAssociation("vertexNormal", 3, GL_FLOAT, mesh.normalOffset(), mesh.vertexSize());
                if(mesh.hasTexCoords()) triple->m_vbo.setAttribAssociation("vertexTexCoord", 2, GL_FLOAT, mesh.texCoordOffset(), mesh.vertexSize());
                if(mesh.hasTangents()) triple->m_vbo.setAttribAssociation("vertexTangent", 3, GL_FLOAT, mesh.tangentOffset(), mesh.vertexSize());

                triple->m_ibo.bind();
        triple->m_vao.unbind();

        // Добавляем меш в список доступных
        m_triples.insert(std::pair<string, Triple*>(meshName, triple));
}

void EntityManager::removeMesh(const string &meshName) {
        MapTriple::iterator it;
        it = m_triples.find(meshName);

        if(it != m_triples.end()) {
                m_triples.erase(it);
        } else {
                DEBUG("Error on removing: mesh with name " << meshName << " is not exist");
        }
}

StringList EntityManager::listOfMeshes() const {
        StringList result;

        MapTriple::iterator it;
        for(it = m_triples.begin(); it != m_triples.end(); ++it) {
                result.push_back(it->first);
        }

        return result;
}

Entity* EntityManager::createEntity(const string &entityName, const string &meshName) {
        // Ищем меш по имени
        MapTriple::iterator it;
        it = m_triples.find(meshName);
        if(it == m_triples.end()) {
                DEBUG("Error on creating entity: mesh with name " << meshName << " is not exist");
                return NULL;
        }

        // Создаем и добавляем новую сущность
        VertexArray* vao = &(it->second->m_vbo);
        Entity* entity = new Entity(vao);
        m_entities->insert(std::pair<string, Entity*>(entityName, entity));

        return entity;
}

Entity* EntityManager::entity(const string &entityName) const {
        MapEntity::iterator it;
        it = m_entities.find(entityName);

        if(it == m_entities.end()) {
                DEBUG("Error on finding entity: Entity with name " << entityName << " not found");
                return NULL;
        } else {
                return it->second;
        }
}

void EntityManager::removeEntity(const string &entityName) {
        MapEntity::iterator it;
        it = m_entities.find(entityName);

        if(it == m_entities.end()) {
                DEBUG("Error on removing entity: Entity with name " << entityName << " not found");
        } else {
                m_entities.erase(it);
        }
}

StringList EntityManager::listOfEntities() const {
        StringList result;

        MapEntity::iterator it;
        for(it = m_entities.begin(); it != m_entities.end(); ++it) {
                result.push_back(it->first);
        }

        return result;
}
