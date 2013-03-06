#ifndef MESH_H
#define MESH_H

#include <string>
#include <glm/glm.hpp>

using glm::vec3;
using glm::vec2;
using std::string;

using namespace std;
using namespace glm;

/** Флаги, определяющие, какие данные должны быть в меше
  */
namespace MeshFlags {
        enum Enum {
                NORMALS = 1,
                TEXCOORDS = 2,
                TANGENTS = 4,

                ALL = 255
        };
}

/** Класс, представляющий собой полигональную сетку,
  * определяющая форму многогранного объекта.
  * Данные о вершинах хранятся в непрерывной области памяти.
  * Формат хранения: |position|[normal]|[texCoord]|[tangent]|...
  */
class Mesh {
private:
        unsigned char*  m_vertices;             //память для хранения атрибутов вершин
        uint            m_verticesCount;        //кол-во вершин
        uint            m_vertexSize;           //размер аттрибутов для одной вершины

        uint*           m_indices;              //память для хранения индексов
        uint            m_indicesCount;         //кол-во идексов

        unsigned char   m_flags;                //определяет, какие данные содержит меш

        uint            m_normalOffset;
        uint            m_texCoordOffset;
        uint            m_tangetOffset;

private:
        // Обнуляет данные члены
        void            init();
        // Освобождает память
        void            freeMemory();

        // Вычисляет смещения offset и размер аттрибутов для одной вершины
        void            calculateOffsets(unsigned char flags);

public:
        Mesh();
        Mesh(const string &filename, size_t indexMesh=0, unsigned char flags=MeshFlags::ALL);
        ~Mesh();

        // Загружает данные меша с индексом indexMesh, из файла filename.
        // Грузятся лишь те данные, которые указаны в flags
        void            loadMeshFromFile(const string &filename, size_t indexMesh=0, unsigned char flags=MeshFlags::ALL);

        // Возвращает указатель на вершинные данные
        void*           vertices() const;
        // Возврашает размеры буфера вершин в байтах
        uint            verticesSize() const;
        // Возвращает размеры одной вершины
        uint            vertexSize() const;

        // Возвращает смещения начал данных о нормалях, текст. коорд, и тангентах
        uint            normalOffset() const;
        uint            texCoordOffset() const;
        uint            tangentOffset() const;

        // Определяет имеет ли меш данные о нормалях, текст. коорд. и тангентах
        bool            hasNormals() const;
        bool            hasTexCoords() const;
        bool            hasTangents() const;

        //Возвращает указатель на индексные данные
        void*           indices() const;
        //Возвращает количество индесов
        uint            indicesCount() const;
        //Вовзращает размер индексных данных
        uint            indicesSize() const;

        // Операторы
        Mesh&           operator=(const Mesh &op2);
};

#endif // MESH_H
