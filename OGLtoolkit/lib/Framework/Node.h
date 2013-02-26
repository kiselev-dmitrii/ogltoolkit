#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>

using glm::vec3;
using namespace glm;

/** Класс представляющий собой систему координат.
  * Нужен для управления движением объектов.
  * Множество различных Node можно организовывать в иерархии.
  * Node можно привязать к объекту типа Movable, для управления этим объектом.
  */
class Node {
private:
        Node*   m_parentNode;

        vec3    m_position;     //позиция в родительской СК
        vec3    m_scale;        //масштаб в родительской СК
        vec3    m_orientation;  //углы эйлера в родительской СК

        mat4    m_localToParent;        //матрица перехода из локальной в родительскую
        bool    m_isNeedToUpdate;       //определяет, нужно ли обновлять матрицы

public:
        // Установка позиции, ориентации, масштаба СК в локальной СК.
        void    setPositionInLocal(const vec3&& pos);
        void    setOrientationInLocal(const vec3& angles);
        void    setScaleInLocal(const vec3& scale);

        // Установка позиции, ориентации, масштаба СК в родительской СК.
        void    setPositionInParent(const vec3&& pos);
        void    setOrientationInParent(const vec3& angles);
        void    setScaleInParent(const vec3& scale);

        // Установка позиции, ориентации, масштаба СК в мировой СК.
        void    setPositionInWorld(const vec3&& pos);
        void    setOrientationInWorld(const vec3& angles);
        void    setScaleInWorld(const vec3& scale);

        // Возвращает позицию, ориентацию, масштаб СК в родительской СК
        vec3    positionInParent() const;
        vec3    orientationInParent() const;
        vec3    scaleInParent() const;

        // Возвращает позицию, ориентацию, масштаб СК в мировой СК
        vec3    positionInWorld() const;
        vec3    orientationInWorld() const;
        vec3    scaleInWorld() const;

        // Возвращает указатель на матрицу перехода от локальной СК в родительскую/мировую
        mat4*   fromLocalToWorld();
        mat4*   fromLocalToParent();

        // Возвращает указатель на матрицу перехода от мировой/родительской СК в локальную
        mat4*   fromWorldToLocal();
        mat4*   fromParentToLocal();
};

#endif // NODE_H
