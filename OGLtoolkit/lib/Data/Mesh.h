#ifndef MESH_H
#define MESH_H

#include <string>
#include <glm/glm.hpp>

using glm::vec3;
using glm::vec2;
using std::string;

using namespace std;
using namespace glm;

/** Структура, содержащая информацию о вершинах меша
  */
struct Vertex {
        vec3    position;
        vec3    normal;
        vec2    texCoord;
};

/** Класс, представляющий собой полигональную сетку,
  * определяющая форму многогранного объекта.
  * Данный класс предполагает, что у меша всегда есть текстурные координаты.
  * Возможно, придется делать вместо массива из Vertex, просто область памяти данных,
  * где будут храниться данные для VBO (без какой либо разметки)
  */
class Mesh {
private:
        Vertex          *m_vertices;
        uint            *m_indices;

        uint            m_verticesCount;
        uint            m_indicesCount;
public:
        Mesh();
        ~Mesh();

        // Загружает модель из файла
        void            loadMeshFromFile(const string &filename);

        // Возвращает указатель на вершинные данные
        void*           vertices();
        // Возврашает размеры буфера вершин в байтах
        uint            verticesSize();

        //Возвращает указатель на индексные данные
        void*           indices();
        //Возвращает количество индесов
        uint            indicesCount();
        //Вовзращает размер индексных данных
        uint            indicesSize();
};

#endif // MESH_H
