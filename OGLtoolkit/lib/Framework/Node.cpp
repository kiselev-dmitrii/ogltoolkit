#include "Node.h"
#include "lib/Utils/Debug.h"
#include <glm/gtc/quaternion.hpp>

Node::Node(const string &name) {
        m_parentNode = NULL;
        m_name = name;
        m_position = vec3(0,0,0);
        m_orientation = quat(1,0,0,0);
        m_scale = vec3(1,1,1);

        m_isNeedToUpdate = true;
}

Node::~Node() {
        TODO;
}

string& Node::name() const {
        return m_name;
}

Node* Node::parentNode() {
        return m_parentNode;
}

void Node::setParentNode(Node *parent) const {
        m_parentNode = parent;
}

Node* Node::childNode(const string &name) const {
        NodeMap::iterator it = m_childNodes.find(name);
        if (it!=m_childNodes.end()) {
                return it->second;
        } else {
                DEBUG("Node " << m_name <<" hasn't child node with name " << name);
                return NULL;
        }
}

void Node::addNode(Node *child) {
        if (child->m_parentNode) {
                DEBUG("Child " << child->m_name << " node already has a parent");
        } else {
                m_childNodes.insert(child->m_name, child);
                child->setParentNode(this);
        }
}

void Node::removeNode(Node *child) {
        m_childNodes.erase(child->m_name);
        child->setParentNode(NULL);
}

void Node::setPositionInParent(const vec3 &position) {
        m_position = position;

        m_isNeedToUpdate = true;
}

void Node::setPositionInWorld(const vec3 &position) {
        //Если имеется родительская нода, то нужно делать преобразование
        //Иначе, это аналогично установки позиции в родительской системе
        if (m_parentNode) {
                // В Ogre наследованная ориентация и наследованный масштаб - это члены класса
                // которые обновляются по запросу
                TRACE("Можно оптимизировать");
                quat derivedOrientation = m_parentNode->m_orientation * m_orientation;
                quat derivedScale = m_parentNode->m_scale * m_scale;
                m_position = (inverse(derivedOrientation) * position)/derivedScale;
        } else {
                m_position = position;
        }

        m_isNeedToUpdate = true;
}

void Node::setOrientationInParent(const quat &orientation) {
        m_orientation = normalize(orientation);
}

void Node::setOrientationInWorld(const quat &orientation) {
        quat normOrientation = normalize(orientation);
        if (m_parentNode) {
                TRACE("Можно оптимизировать");
                quat derivedOrientation = m_parentNode->m_orientation * m_orientation;
                m_orientation = inverse(derivedOrientation) * normOrientation * derivedOrientation;
        } else {
                m_orientation = normOrientation;
        }
}

void Node::translateInParent(const vec3 &delta) {
        m_position += delta;
}

void Node::translateInLocal(const vec3 &delta) {
        m_position += m_orientation * delta;
}

void Node::translateInWorld(const vec3 &delta) {
        if (m_parentNode) {
                //В Ogre вызывается m_parent->derivedOrientation()
                TRACE("Возможно не верно работает");
                quat derivedOrientation = m_parentNode->m_orientation * m_orientation;
                quat derivedScale = m_parentNode->m_scale * m_scale;
                m_position += (inverse(derivedOrientation) * delta) / derivedScale;
        } else {
                m_position += delta;
        }
}

void Node::rotateInParent(const quat &quaternion) {
        m_orientation = normalize(quaternion) * m_orientation;
}

void Node::rotateInLocal(const quat &quaternion) {
        m_orientation = m_orientation * normalize(quaternion);
}

void Node::rotateInWorld(const quat &quaternion) {
        TRACE("Возможно не верно работает");
        quat derivedOrientation = m_parentNode->m_orientation * m_orientation;
        m_orientation = m_orientation * inverse(derivedOrientation) * normalize(quaternion) * derivedOrientation;
}
