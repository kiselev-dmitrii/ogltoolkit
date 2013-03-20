#include "SceneManager.h"
#include "lib/Utils/Debug.h"

SceneManager::SceneManager() { }

SceneManager* SceneManager::instance() {
        static SceneManager instance;
        return &instance;
}

SceneManager::~SceneManager() {
        TODO;
}

SceneNode* SceneManager::rootNode() {
        return &m_rootNode;
}

AbstractCamera* SceneManager::addCamera(const string &cameraName, AbstractCamera *camera) {
        m_cameras.insert(std::pair<string, AbstractCamera*>(cameraName, camera));
        return camera;
}

void SceneManager::removeCamera(const string &cameraName) {
        MapAbstractCamera::iterator it;
        it = m_cameras.find(cameraName);

        if(it != m_cameras.end()) {
                delete it->second;
                m_cameras.erase(it);
        } else {
                DEBUG("Error on removing: camera with name " << cameraName << " is not exist");
        }
}

AbstractCamera* SceneManager::camera(const string &cameraName) const {
        MapAbstractCamera::const_iterator it;
        it = m_cameras.find(cameraName);

        if(it != m_cameras.end()) {
                return it->second;
        } else {
                DEBUG("Error on finding: camera with name " << cameraName << " is not exist");
                return NULL;
        }
}
