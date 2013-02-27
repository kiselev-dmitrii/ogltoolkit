#ifndef MOVABLE_H
#define MOVABLE_H

#include "Node.h"

/** Базовый класс всех сущностей, которые могут изменять свое положение, размер, ориентацию.
  */
class Movable {
private:
        Node*   m_node;         //узел, к которому привязан объект

public:
        Movable(Node* node=NULL);

        // Возвращает систему координат с которой связан объект
        Node*   node();
        // Присоединяет объект к системе координат
        void    setNode(Node* node);
};

#endif // MOVABLE_H
