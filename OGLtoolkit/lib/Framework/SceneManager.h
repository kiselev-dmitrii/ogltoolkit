#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <map>
#include "SceneNode.h"

using namespace std;

class SceneNode;
class AbstractCamera;

typedef map<string, AbstractCamera*>    MapAbstractCamera;

/** Занимается управлением всех объектов на сцене
  * Включает в себя методы управления другими менеджерами для удобства
  */
class SceneManager {
private:
        MapAbstractCamera       m_cameras;      //коллекция камер
        SceneNode               m_rootNode;     //корневая нода

private:
        // Закрытые конструкторы
        SceneManager();
        SceneManager(const SceneManager&);
        SceneManager& operator=(const SceneManager&);

public:
        // Точка доступа
        static SceneManager* instance();
        // Деструктор
        ~SceneManager();

        // Возвращает корневую ноду сцены
        SceneNode*      rootNode();

        // Добавляет новую камеру
        AbstractCamera* addCamera(const string& cameraName,  AbstractCamera* camera);
        // Удаляет камеру
        void            removeCamera(const string& cameraName);
        // Возвращает указатель на камеру
        AbstractCamera* camera(const string& cameraName) const;

};

#endif // SCENEMANAGER_H
