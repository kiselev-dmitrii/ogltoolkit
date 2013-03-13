#include "BoundBox.h"

BoundBox::BoundBox(const vec3 &minCoords, const vec3 &maxCoords) {
        setGeometry(minCoords, maxCoords);
}

void BoundBox::setGeometry(const vec3 &minCoords, const vec3 &maxCoords) {
        float verices[] = {
                minCoords.x, minCoords.y, minCoords.z,
                minCoords.x, minCoords.y, maxCoords.z,
                minCoords.x, maxCoords.y, minCoords.z,
                minCoords.x, maxCoords.y, maxCoords.z,
                maxCoords.x, minCoords.y, minCoords.z,
                maxCoords.x, minCoords.y, maxCoords.z,
                maxCoords.x, maxCoords.y, minCoords.z,
                maxCoords.x, maxCoords.y, maxCoords.z
        };
        GLuint indices[] = {1,7,5,
                            1,3,7,
                            1,4,3,
                            1,2,4,
                            3,8,7,
                            3,4,8,
                            5,7,8,
                            5,8,6,
                            1,5,6,
                            1,6,2,
                            2,6,8,
                            2,8,4};

        // Загружаем данные
        m_meshInfo.vertexBuffer()->uploadData(verices, 3*8*sizeof(float), Hint::STREAM_DRAW);
        m_meshInfo.indexBuffer()->uploadData(indices, 3*12*sizeof(GLuint), Hint::STREAM_DRAW);

        m_meshInfo.vertexArray()->bind();
                m_meshInfo.vertexBuffer()->setAttribAssociation("vertexPosition", 3, GL_FLOAT);
                m_meshInfo.indexBuffer()->bind();
        m_meshInfo.vertexArray()->unbind();

        m_meshInfo.setIndicesCount(3*12);
}

MeshInfo* BoundBox::meshInfo() {
        return &m_meshInfo;
}
