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

typedef vector<string> StringList;

/** Данные о меше
  * Указатель на эти данные имеет каждый объект Entity.
  * Они затем используются при ренедере
  */
struct MeshInfo {
        VertexBuffer    m_vbo;
        IndexBuffer     m_ibo;
        VertexArray     m_vao;

        uint            m_indicesCount;
};


/** Класс представляет собой фабрику объектов типа Entity
  * Представляет методы для загрузки мешей в видеопамять и
  * для доступа и создания объектов Entity из загруженных мешей
  *
  * Для создания объекта типа Entity, требуется сначала загрузить в менеджер Mesh,
  * после чего данный меш будет загружен в видеопамять и именован. После этого по имени
  * можно будет создать несколько Entity с одним и тем же мешем.
  *
  * Данный класс скорее всего будет изменен либо удален, так как есть минусы:
  *     - Неиспользуемые меши (в видеопамяти) не удаляются автоматически
  *     - Данный класс выполняет некоторую работу по загрузке ресурсов, это должен делать менеджер ресурсов.
  */
class EntityManager {
private:
        typedef map<string, MeshInfo*> MapMeshInfo;
        typedef map<string, Entity*> MapEntity;

private:
        MapMeshInfo     m_meshes;       //меши
        MapEntity       m_entities;     //сущности

public:
        // Конструктор
        EntityManager();
        // Деструктор
        ~EntityManager();

        // Добавляет меш для дальнейшего использования
        void            addMesh(const Mesh& mesh, const string& meshName);
        // Удаляет меш из доступных
        void            removeMesh(const string& meshName);
        // Удаляет все меши
        void            removeAllMeshes();
        // Возвращает список доступных мешей
        StringList      listOfMeshes() const;


        // Создает объект Entity c именем entityName и мешем meshName.
        // Меш должен быть предварительно загружен
        Entity*         createEntity(const string& entityName, const string& meshName);
        // Возвращает указатель на уже созданый объект entityName
        Entity*         entity(const string& entityName) const;
        // Удаляет объект с именем entityName
        void            removeEntity(const string& entityName);
        // Удаляет все сущности
        void            removeAllEntities();
        // Возвращает список созданных Entity
        StringList      listOfEntities() const;

};

#endif // ENTITYMANAGER_H
