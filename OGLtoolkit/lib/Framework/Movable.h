#ifndef MOVABLE_H
#define MOVABLE_H

#include "SceneNode.h"

/** Базовый класс всех сущностей, которые могут изменять свое положение, размер, ориентацию.
  */
class Movable {
private:
        SceneNode*      m_node;         //узел, к которому привязан объект

public:
        Movable(SceneNode* node=NULL);

        // Возвращает систему координат с которой связан объект
        SceneNode*      node();
        // Присоединяет объект к системе координат
        void            setNode(SceneNode* node);

        // Возвращает матрицы пеерхода от локальных координат к мировым и наоборот
        const mat4&     localToWorldMatrix();
        const mat4&     worldToLocalMatrix();
};

#endif // MOVABLE_H
