#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>

using namespace std;

class SceneNode;
class AbstractCamera;

/** Занимается управлением всех объектов на сцене
  */
class SceneManager {
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

        // Добавляет новую камеру и привязывает ее к ноде
        AbstractCamera* addCamera(const string& cameraName, SceneNode* node, AbstractCamera* camera);
        // Добавляет новую камеру и создает ноду
        AbstractCamera* addCamera(const string& cameraName, AbstractCamera* camera);
        // Удаляет камеру
        void            removeCamera(const string& cameraName);
        // Возвращает указатель на камеру
        AbstractCamera* camera(const string& cameraName);



};

#endif // SCENEMANAGER_H
