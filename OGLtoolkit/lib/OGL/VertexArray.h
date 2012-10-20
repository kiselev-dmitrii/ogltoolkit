#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>

/** Класс-обертка для объекта VertexArrayObject
  */
class VertexArray {
private:
        GLuint  m_handle;
public:
        // Создает экземпляр VAO
        VertexArray();
        // Удаляет экзепляр VAO
        ~VertexArray();

        // Делает VAO текущим
        void    bind();
        // Отключает данный VAO
        void    unbind();

        // Возвращает handle
        GLuint  handle();
};

#endif // VERTEXARRAY_H
