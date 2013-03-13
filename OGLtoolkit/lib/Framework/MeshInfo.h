#ifndef MESHINFO_H
#define MESHINFO_H

#include "lib/Core/OpenGL/VertexBuffer.h"
#include "lib/Core/OpenGL/IndexBuffer.h"
#include "lib/Core/OpenGL/VertexArray.h"

/** Данные о меше
  * Указатель на эти данные имеет каждый объект Entity.
  * Они затем используются при ренедере
  */
class MeshInfo {
private:
        VertexBuffer    m_vbo;
        IndexBuffer     m_ibo;
        VertexArray     m_vao;

        unsigned int    m_indicesCount;

public:
        // Возвращает укащатели на VBO, VAO, IBO
        VertexBuffer*   vertexBuffer() const;
        IndexBuffer*    indexBuffer() const;
        VertexArray*    vertexArray() const;

        // Установить/получить количество индексов
        unsigned int    indicesCount() const;
        void            setIndicesCount(unsigned int count);
};

#endif // MESHINFO_H
