#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "TreeNode.h"

using namespace glm;
using glm::vec3;
using glm::quat;

/** Иерархические вложенные системы координат.
  * К каждому узлу можно подключить дочерний узел и т.д
  * Это также называется графом сцены.
  * Наследуется от TreeNode. Здесь часто будет применятся приведенние TreeNode* к SceneNode*
  */
class SceneNode : public TreeNode {
private:
        vec3    m_position;             //позиция, относительно родительской СК
        quat    m_orientation;          //ориентация, относительно родительской СК
        vec3    m_scale;                //масштаб, относительно родительской СК

        vec3    m_positionInWorld;      //позиция, относительно мировой СК
        quat    m_orientationInWorld;   //оринетация, относительно мировой СК
        vec3    m_scaleInWorld;         //масштаб, относительно мировой СК

        bool    m_isNeedToUpdate;       //определяет, требуется ли обновление

private:
        // Инициализация начальных значений
        void    init();

        // Обновление positionInWorld и т.д
        void    update();

public:
        // Конструирует СК с именем Unknown_i
        SceneNode();
        // Конструирует СК с именем name
        SceneNode(const string& name);
        // Разрушает СК
        ~SceneNode();

        // Возвращает позицию/ориентацию в мировых координатах
        const vec3&     positionInWorld();
        const quat&     orientationInWorld();
        const vec3&     scaleInWorld();


        virtual void    onAddChild();
        virtual void    onRemoveChild();
};

#endif // SCENENODE_H
