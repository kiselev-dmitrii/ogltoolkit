#include "MeshInfo.h"

VertexBuffer* MeshInfo::vertexBuffer() {
        return &m_vbo;
}

IndexBuffer* MeshInfo::indexBuffer() {
        return &m_ibo;
}

VertexArray* MeshInfo::vertexArray() {
        return &m_vao;
}

void MeshInfo::setIndicesCount(unsigned int count) {
        m_indicesCount = count;
}

unsigned int MeshInfo::indicesCount() const {
        return m_indicesCount;
}
