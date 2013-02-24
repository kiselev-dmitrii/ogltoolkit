#include "VertexArray.h"

VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_handle);
}

VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_handle);
}

void VertexArray::bind() {
        glBindVertexArray(m_handle);
}

void VertexArray::unbind() {
        glBindVertexArray(0);
}

GLuint VertexArray::handle() {
        return m_handle;
}
