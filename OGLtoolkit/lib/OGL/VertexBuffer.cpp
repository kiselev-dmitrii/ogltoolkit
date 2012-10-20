#include "VertexBuffer.h"
#include "lib/Debug/Debug.h"

VertexBuffer::VertexBuffer() : BufferObject(Target::ARRAY_BUFFER) {
}

void VertexBuffer::setAttribAssociation(GLuint attrIndex, GLuint attrSize, GLenum attrType, GLsizei offset, GLsizei stride) {
        glBindBuffer(m_target, m_handle);
        glEnableVertexAttribArray(attrIndex);           //делает аттрибут активным для VBO
        glVertexAttribPointer(attrIndex, attrSize, attrType, GL_FALSE, stride, (GLubyte *)offset);
}

void VertexBuffer::setAttribAssociation(const string &attrName, GLuint attrSize, GLenum attrType, GLsizei offset, GLsizei stride) {
        glBindBuffer(m_target, m_handle);

        // Получаем индекс аттрибута
        GLint curProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &curProgram);
        GLuint attrIndex = glGetAttribLocation(curProgram, attrName.c_str());

        // Собственно связываем
        glEnableVertexAttribArray(attrIndex);           //делает аттрибут активным для VBO
        glVertexAttribPointer(attrIndex, attrSize, attrType, GL_FALSE, stride, (GLubyte *)offset);
}



