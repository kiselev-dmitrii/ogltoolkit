#include "EntityManager.h"
#include "MeshManager.h"
#include "lib/Utils/Debug.h"

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
        removeAllEntities();
}

EntityManager* EntityManager::instance() {
        static EntityManager instance;
        return &instance;
}

Entity* EntityManager::createEntity(const string &entityName, const string &meshName) {
        MeshInfo* mesh = MeshManager::instance()->mesh(meshName);
        if(mesh) {
                Entity* entity = new Entity(mesh);
                m_entities.insert(std::pair<string, Entity*>(entityName, entity));
                return entity;
        } else {
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

Entity* EntityManager::entity(const string &entityName) const {
        MapEntity::const_iterator it;
        it = m_entities.find(entityName);

        if(it != m_entities.end()) {
                return it->second;
        } else {
                DEBUG("Error on finding entity: Entity with name " << entityName << " not found");
                return NULL;
        }
}

MapEntity* EntityManager::entities() const {
        return m_entities;
}

StringList EntityManager::listOfEntities() const {
        StringList result;

        MapEntity::const_iterator it;
        for(it = m_entities.begin(); it != m_entities.end(); ++it) {
                result.push_back(it->first);
        }

        return result;
}
