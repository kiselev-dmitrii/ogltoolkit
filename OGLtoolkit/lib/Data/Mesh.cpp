#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Debug/Debug.h"

void Mesh::init() {
        m_vertices = NULL;
        m_verticesCount = 0;
        m_vertexSize = 0;

        m_indices = NULL;
        m_indicesCount = 0;

        m_flags = 0;

        m_normalOffset = 0;
        m_texCoordOffset = 0;
        m_tangetOffset = 0;

}

void Mesh::freeMemory() {
        if (m_vertices != NULL) delete [] m_vertices;
        if (m_indices != NULL) delete [] m_indices;
}

void Mesh::calculateOffsets(unsigned char flags) {
        uint positionSize = 3*sizeof(float);
        uint normalSize = 0;
        uint texCoordSize = 0;
        uint tangentSize = 0;

        m_vertexSize = positionSize;
        if(m_flags & MeshFlags::NORMALS) {
                normalSize = 3*sizeof(float);
                m_vertexSize += normalSize;
                m_normalOffset = positionSize;
        }
        if(m_flags & MeshFlags::TEXCOORDS) {
                texCoordSize = 2*sizeof(float);
                m_vertexSize += texCoordSize;
                m_texCoordOffset = positionSize + normalSize;
        }
        if(m_flags & MeshFlags::TANGENTS) {
                tangentSize = 3*sizeof(float);
                m_vertexSize += tangentSize;
                m_tangetOffset = positionSize + normalSize + texCoordSize;
        }
}

Mesh::Mesh() {
        init();
}

Mesh::Mesh(const string &filename, size_t indexMesh, unsigned char flags) {
        init();
        loadMeshFromFile(filename, indexMesh, flags);
}

Mesh::~Mesh() {
        freeMemory();
}

void Mesh::loadMeshFromFile(const string &filename, size_t indexMesh, unsigned char flags) {
        // Освобождаем память от предыдущего меша
        freeMemory();
        init();

        // Загружаем новый меш
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Quality);
        if(!scene) {
                DEBUG("Error loading mesh from " << filename);
                DEBUG(importer.GetErrorString());
                return;
        }

        // Проверяем, имеется ли достаточное кол-во мешей
        if(scene->mNumMeshes <= indexMesh) {
                DEBUG("Error: " << filename << " has just" << scene->mNumMeshes << " meshes");
                return;
        }
        const aiMesh *mesh = scene->mMeshes[indexMesh];

        // Проверяем есть ли запрашиваемая во flags информация
        // Если нет, то корректируем m_flags
        m_flags = flags;
        if(!mesh->HasPositions()) {
                DEBUG("Error: File " << filename << " does not contain positions");
                return;
        }
        if(!mesh->HasNormals() && (m_flags & MeshFlags::NORMALS)) {
                DEBUG("Warning: File " << filename << " does not contain normals. Miss.");
                m_flags = m_flags & ~MeshFlags::NORMALS;
        }
        if(!mesh->HasTextureCoords(0) && (m_flags & MeshFlags::TEXCOORDS)) {
                DEBUG("Warning: File " << filename << " does not contain texture coordinate. Miss.");
                m_flags = m_flags & ~MeshFlags::TEXCOORDS;
        }
        if(!mesh->HasTangentsAndBitangents() && (m_flags & MeshFlags::TANGENTS)) {
                DEBUG("Warning: File " << filename << " does not contain tangent. Miss.");
                m_flags = m_flags & ~MeshFlags::TANGENTS;
        }

        // Проходим по всем граням и копируем индексы в m_indices.
        // Каждая грань - это треугольник
        m_indicesCount = mesh->mNumFaces * 3;
        m_indices = new uint [m_indicesCount];
        for(size_t i=0; i < mesh->mNumFaces; ++i) {
                const aiFace* face = &(mesh->mFaces[i]);
                memcpy(&(m_indices[i*3]), face->mIndices, sizeof(uint)*3);
        }

        // Вычисляем смещения и m_vertexSize
        calculateOffsets(m_flags);

        // Заполняем вершины
        m_verticesCount = mesh->mNumVertices;
        m_vertices = new unsigned char [m_verticesCount * m_vertexSize];

        // Позиции
        for(size_t i=0, pos=0; i < m_verticesCount; ++i, pos += m_vertexSize) {
                memcpy(m_vertices+pos, mesh->mVertices+i, 3*sizeof(float));
        }
        // Нормали
        if(hasNormals()) {
                for(size_t i=0, pos=m_normalOffset; i < m_verticesCount; ++i, pos += m_vertexSize) {
                        memcpy(m_vertices+pos, mesh->mNormals+i, 3*sizeof(float));
                }
        }
        // Текст. координаты
        if(hasTexCoords()) {
                for(size_t i=0, pos=m_texCoordOffset; i < m_verticesCount; ++i, pos += m_vertexSize) {
                        memcpy(m_vertices+pos, mesh->mTextureCoords[0]+i, 2*sizeof(float));
                }
        }
        // Тангенты
        if(hasTangents()) {
                for(size_t i=0, pos=m_tangetOffset; i < m_verticesCount; ++i, pos += m_vertexSize) {
                        memcpy(m_vertices+pos, mesh->mTangents+i, 3*sizeof(float));
                }
        }
}


void *Mesh::vertices() { return (void *)m_vertices; }

uint Mesh::verticesSize() { return m_verticesCount * m_vertexSize; }

uint Mesh::vertexSize() { return m_vertexSize; }

uint Mesh::normalOffset() { return m_normalOffset; }

uint Mesh::texCoordOffset() { return m_texCoordOffset; }

uint Mesh::tangentOffset() { return m_tangetOffset; }

bool Mesh::hasNormals() { return m_flags & MeshFlags::NORMALS; }

bool Mesh::hasTexCoords() { return m_flags & MeshFlags::TEXCOORDS; }

bool Mesh::hasTangents() { return m_flags & MeshFlags::TANGENTS; }

void *Mesh::indices() { return (void *)m_indices; }

uint Mesh::indicesCount() { return m_indicesCount; }

uint Mesh::indicesSize() { return m_indicesCount * sizeof(uint); }

Mesh &Mesh::operator =(const Mesh &op2) {
        freeMemory();

        m_verticesCount = op2.m_verticesCount;
        m_vertexSize = op2.m_vertexSize;
        m_indicesCount = op2.m_indicesCount;
        m_flags = op2.m_flags;
        m_normalOffset = op2.m_normalOffset;
        m_texCoordOffset = op2.m_texCoordOffset;
        m_tangetOffset = op2.m_tangetOffset;

        m_vertices = new unsigned char [m_verticesCount * m_vertexSize];
        m_indices = new uint [m_indicesCount];

        memcpy(m_vertices, op2.m_vertices, m_verticesCount * m_vertexSize);
        memcpy(m_indices, op2.m_indices, m_indicesCount * sizeof(uint));
}
