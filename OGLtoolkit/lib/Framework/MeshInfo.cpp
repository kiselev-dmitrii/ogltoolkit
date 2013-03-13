#include "MeshInfo.h"

VertexBuffer* MeshInfo::vertexBuffer() const {
        return &m_vbo;
}

IndexBuffer* MeshInfo::indexBuffer() const {
        return &m_ibo;
}

VertexArray* MeshInfo::vertexArray() const {
        return &m_vao;
}

void MeshInfo::setIndicesCount(unsigned int count) {
        m_indicesCount = count;
}

unsigned int MeshInfo::indicesCount() const {
        return m_indicesCount;
}
