#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "BufferObject.h"

/** Класс-обертка для Vertex Buffer Object
  */
class VertexBuffer : public BufferObject {
public:
        // Создает экземпляр VBO
        VertexBuffer();

        // Устанавливает ассоциацию между данными в VBO и атрибутом
        void setAttribAssociation(GLuint attrIndex, GLuint attrSize, GLenum attrType, GLsizei offset=0, GLsizei stride=0);
        void setAttribAssociation(const string &attrName, GLuint attrSize, GLenum attrType, GLsizei offset=0, GLsizei stride=0);
};

#endif // VERTEXBUFFER_H
