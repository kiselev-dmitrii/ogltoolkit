#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Debug/Debug.h"

Mesh::Mesh() {
        m_vertices = NULL;
        m_indices = NULL;
        m_verticesCount = 0;
        m_indicesCount = 0;
}

Mesh::~Mesh() {
        if (m_vertices != NULL) delete [] m_vertices;
        if (m_indices != NULL) delete [] m_indices;
}

void Mesh::loadMeshFromFile(const string &filename) {
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Quality);
        if (!scene) {
                DEBUG("Error loading mesh from " << filename);
                DEBUG(importer.GetErrorString());
                return;
        }

        // Будем считать что в файле один меш
        if (scene->mNumMeshes != 1) {
                DEBUG("Error: " << filename << " has " << scene->mNumMeshes << " meshes");
                return;
        }
        const aiMesh *mesh = scene->mMeshes[0];

        // Будем считать, что в файле есть позиция вершин, нормалей и текстурные координаты
        if (!mesh->HasPositions() || !mesh->HasNormals() || !mesh->HasTextureCoords(0)) {
                DEBUG("Error: " << filename << " has not enough data");
                return;
        }

        // Если меш уже был, то удаляем его
        if (m_vertices != NULL) {
                delete [] m_vertices;
                m_verticesCount = 0;
        }
        if (m_indices != NULL) {
                delete [] m_indices;
                m_indicesCount = 0;
        }

        // Проходим по всем граням и копируем индексы в m_indices.
        // Каждая грань - это треугольник
        m_indicesCount = mesh->mNumFaces * 3;
        m_indices = new uint [mesh->mNumFaces * 3];
        for (size_t i=0; i < mesh->mNumFaces; ++i) {
                const aiFace* face = &(mesh->mFaces[i]);
                memcpy(&(m_indices[i*3]), face->mIndices, sizeof(uint)*3);
        }

        // Заполняем вершины
        m_verticesCount = mesh->mNumVertices;
        m_vertices = new Vertex [m_verticesCount];
        for (size_t i=0; i < m_verticesCount; ++i) {
                memcpy(&(m_vertices[i].position[0]), mesh->mVertices+i, 3*sizeof(float));
                memcpy(&(m_vertices[i].normal[0]), mesh->mNormals+i, 3*sizeof(float));
                memcpy(&(m_vertices[i].texCoord[0]), mesh->mTextureCoords+i, 2*sizeof(float));
        }
}


void *Mesh::vertices() {
        return (void *)m_vertices;
}

uint Mesh::verticesSize() {
        return m_verticesCount * sizeof(Vertex);
}

void *Mesh::indices() {
        return (void *)m_indices;
}

uint Mesh::indicesCount() {
        return m_indicesCount;
}

uint Mesh::indicesSize() {
        return m_indicesCount * sizeof(uint);
}
