#ifndef ENTITY_H
#define ENTITY_H

#include "lib/Core/OpenGL/VertexArray.h"
#include "lib/Core/OpenGL/VertexBuffer.h"
#include "lib/Core/OpenGL/IndexBuffer.h"
#include "lib/Core/Data/Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using glm::vec3;
using glm::mat3;
using std::string;

/** Класс, служащий для представления игровых объектов
  */
class Entity {
private:
        mat4            m_modelMatrix;
        bool            m_isModelMatrixChanged;

        Mesh            m_mesh;
        VertexArray     m_vao;
        VertexBuffer    m_vbo;
        IndexBuffer     m_ibo;

        vec3            m_position;             //позиция
        vec3            m_orientation;          //оринтация
        vec3            m_scale;                //масштаб
        vec3            m_pivot;                //точка вращения
private:
        // Обновляет данные в VBO, IBO
        void            updateBuffers();
        // Обновляет состояние VAO
        void            updateInterpretation();

        //Инициализирует вектора позиции, ориентации и т.д
        void            init();
public:
        // Пустой объект. Далее в него загружается меш с помощью setMesh
        Entity();
        // Создает 3d объект с мешем из файла filename
        Entity(const string &filename);
        // Создает 3d объект с мешем mesh
        Entity(const Mesh &mesh);

        // Устанавливает/возвращает меш
        void            setMesh(const Mesh &mesh);
        void            setMesh(const string &filename);
        Mesh*           mesh();

        //Устанавливает позицию и ориентацию объекта в пространстве
        void            setPosition(const vec3 &pos);
        void            setOrientation(const vec3 &angles);
        void            setScale(const vec3 &scales);
        //Изменяет позицию/ориентацию/растяжение на delta
        void            move(const vec3 &delta);
        void            rotate(const vec3 &delta);
        void            stretch(const vec3 &delta);
        //Возвращает позицию/ориентацию/масштаб объекта
        vec3            position();
        vec3            orientation();
        vec3            scale();

        // Устанавливает точку вращения
        void            setPivot(const vec3 &coord);
        // Возвращает точку вращения
        vec3            pivot();

        //Возвращает указатель на модельную матрицу
        mat4*           modelMatrix();
        //Возвращает указатель на vao
        VertexArray*    vertexArray();
};

#endif // ENTITY_H
