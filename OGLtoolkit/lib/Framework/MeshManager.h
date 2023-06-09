#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "lib/Core/Data/Mesh.h"
#include "MeshInfo.h"

typedef vector<string> StringList;
typedef map<string, MeshInfo*> MapMeshInfo;

/** Синглтон.
  * Используется для загрузки мешей в видеопамять.
  * Для доступа к мешу используется его имя.
  * По своей сути, представляет собой ресурс-менеджер для мешей.
  * Также предоставляет возможности генерирования некоторых примитивов
  * Вершины загруженного в память меша имеют следующие аттрибуты:
  *     - _vertexPosition       - позиция вершины в модельных коориднатах
  *     - _vertexNormal         - нормаль к вершине
  *     - _vertexTexCoord       - текстурные координаты
  *     - _vertexTangent        - тангент вектор
  */
class MeshManager {
private:
        MapMeshInfo     m_meshes;       //информация о мешах

private:
        // Закрытые конструкторы и оператор присваивания
        MeshManager();
        MeshManager(const MeshManager&);
        MeshManager& operator=(const MeshManager&);

public:
        // Точка доступа к объекту
        static MeshManager* instance();
        // Деструктор
        ~MeshManager();

        // Загрузить меш. Загрузка по-умолчанию идет из директории с ресурсами
        void            loadMesh(const string& meshName, const string& filename, size_t indexMesh=0, unsigned char flags=MeshFlags::ALL);
        void            loadMesh(const string& meshName, const Mesh& mesh);

        // Обновляет меш новыми данными
        void            updateMesh(const string& meshName, const Mesh& mesh);

        // Удаляет меш из доступных
        void            removeMesh(const string& meshName);
        void            removeAllMeshes();

        // Возвращает меш по имени
        MeshInfo*       mesh(const string& meshName) const;

        // Вовзращает список доступных мешей
        StringList      listOfMeshes() const;

};

#endif // MESHMANAGER_H
