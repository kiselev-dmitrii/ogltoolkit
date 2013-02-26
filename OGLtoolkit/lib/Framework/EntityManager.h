#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "lib/Core/OpenGL/VertexBuffer.h"
#include "lib/Core/OpenGL/IndexBuffer.h"
#include "lib/Core/OpenGL/VertexArray.h"
#include "lib/Core/Data/Mesh.h"
#include "lib/Framework/Entity.h"

using std::map;
using std::string;
using namespace std;

/** Класс представляет собой фабрику объектов типа Entity
  * Представляет методы для загрузки мешей в видеопамять и
  * для доступа и создания объектов Entity из загруженных мешей
  */
class EntityManager {
private:
        struct Triple {
                VertexBuffer    m_vbo;
                IndexBuffer     m_ibo;
                VertexArray     m_vao;
        };

        map<string, Triple>     m_meshes;       //меши в видеопамяти
        map<string, Entity>     m_entities;     //сущности

public:
        // Добавляет меш для дальнейшего использования
        void            addMesh(const Mesh& mesh, const string& meshName);
        void            addMesh(const string& path, const string& meshName);

        // Удаляет меш из доступных
        void            removeMesh(const string& meshName);

        // Возвращает список доступных мешей
        vector<string>  listOfMeshes() const;


        // Создает объект Entity c именем entityName и мешем meshName.
        // Меш должен быть предварительно загружен
        Entity*         createEntity(const string& entityName, const string& meshName);

        // Возвращает указатель на уже созданый объект entityName
        Entity*         entity(const string& entityName);

        // Удаляет объект с именем entityName
        void            removeEntity(const string& entityName);

        // Возвращает список созданных Entity
        vector<string>  listOfEntities() const;
};

#endif // ENTITYMANAGER_H
