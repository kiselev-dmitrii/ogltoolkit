#include "Movable.h"

Movable::Movable(SceneNode *node) {
        m_node = node;
}

SceneNode* Movable::node() {
        return m_node;
}

void Movable::setNode(SceneNode *node) {
        m_node = node;
}

const mat4& Movable::localToWorldMatrix() {
        return m_node->localToWorldMatrix();
}

const mat4& Movable::worldToLocalMatrix() {
        return m_node->worldToLocalMatrix();
}


