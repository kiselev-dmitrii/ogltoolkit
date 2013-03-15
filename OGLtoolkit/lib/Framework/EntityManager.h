#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Entity.h"

using std::map;
using std::string;
using namespace std;

typedef vector<string> StringList;
typedef map<string, Entity*> MapEntity;

/** Синглтон.
  * Представляет собой фабрику для объектов типа Entity
  * Представляет методы для доступа и создания объектов Entity из загруженных мешей.
  */
class EntityManager {
private:
        MapEntity       m_entities;     //сущности

private:
        //Закрытые конструктори и оператор присваивания
        EntityManager();
        EntityManager(const EntityManager&);
        EntityManager& operator=(const EntityManager&);

public:
        // Точка доступа к объекту
        static EntityManager* instance();
        // Деструктор
        ~EntityManager();

        // Создает объект Entity c именем entityName и доступным мешем meshName.
        Entity*         createEntity(const string& entityName, const string& meshName);

        // Удаляет сущность
        void            removeEntity(const string& entityName);
        void            removeAllEntities();

        // Возвращает указатель на сущность или на коллекцию сущностей
        Entity*         entity(const string& entityName) const;
        MapEntity*      entities() const;

        // Возвращает список созданных Entity
        StringList      listOfEntities() const;

};

#endif // ENTITYMANAGER_H
