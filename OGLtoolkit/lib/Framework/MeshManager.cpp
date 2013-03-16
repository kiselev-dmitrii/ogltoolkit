#include "MeshManager.h"
#include "lib/Utils/Debug.h"

MeshManager::MeshManager() { }

MeshManager::~MeshManager() {
        removeAllMeshes();
}

MeshManager* MeshManager::instance() {
        static MeshManager instance;
        return &instance;
}

void MeshManager::loadMesh(const string &meshName, const Mesh &mesh) {
        // Создаем VBO, IBO, VAO и загружаем туда данные меша
        MeshInfo* meshInfo = new MeshInfo();
        meshInfo->vertexBuffer()->uploadData(mesh.vertices(), mesh.verticesSize(), Hint::STATIC_DRAW);
        meshInfo->indexBuffer()->uploadData(mesh.indices(), mesh.indicesSize(), Hint::STATIC_DRAW);

        // Настраиваем VAO (задаем, как должны интерпретировать аттрибуты и т.д
        meshInfo->vertexArray()->bind();
                meshInfo->vertexBuffer()->setAttribAssociation("_vertexPosition", 3, GL_FLOAT, 0, mesh.vertexSize());

                if(mesh.hasNormals()) meshInfo->vertexBuffer()->setAttribAssociation("_vertexNormal", 3, GL_FLOAT, mesh.normalOffset(), mesh.vertexSize());
                if(mesh.hasTexCoords()) meshInfo->vertexBuffer()->setAttribAssociation("_vertexTexCoord", 2, GL_FLOAT, mesh.texCoordOffset(), mesh.vertexSize());
                if(mesh.hasTangents()) meshInfo->vertexBuffer()->setAttribAssociation("_vertexTangent", 3, GL_FLOAT, mesh.tangentOffset(), mesh.vertexSize());

                meshInfo->indexBuffer()->bind();
        meshInfo->vertexArray()->unbind();

        // Указываем количество индексов в меше
        meshInfo->setIndicesCount(mesh.indicesCount());

        // Добавляем меш в список доступных
        m_meshes.insert(std::pair<string, MeshInfo*>(meshName, meshInfo));
}

void MeshManager::loadMesh(const string &meshName, const string &filename, size_t indexMesh, unsigned char flags) {
        loadMesh(meshName, Mesh(filename, indexMesh, flags));
}

void MeshManager::removeMesh(const string &meshName) {
        MapMeshInfo::iterator it;
        it = m_meshes.find(meshName);

        if(it != m_meshes.end()) {
                delete it->second;
                m_meshes.erase(it);
        } else {
                DEBUG("Error on removing: mesh with name " << meshName << " is not exist");
        }
}

void MeshManager::removeAllMeshes() {
        MapMeshInfo::iterator it;
        for(it = m_meshes.begin(); it != m_meshes.end(); ++it) {
                delete it->second;
        }
        m_meshes.erase(m_meshes.begin(), m_meshes.end());
}

MeshInfo* MeshManager::mesh(const string &meshName) const {
        MapMeshInfo::const_iterator it;
        it = m_meshes.find(meshName);

        if(it != m_meshes.end()) {
                return it->second;
        } else {
                DEBUG("Error on finding mesh: Mesh with name " << meshName << " not found");
                return NULL;
        }
}

StringList MeshManager::listOfMeshes() const {
        StringList result;

        MapMeshInfo::const_iterator it;
        for(it = m_meshes.begin(); it != m_meshes.end(); ++it) {
                result.push_back(it->first);
        }

        return result;
}
