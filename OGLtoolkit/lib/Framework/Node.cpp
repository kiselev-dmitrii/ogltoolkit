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
        // В OGRE каждая нода хранит
        TRACE("Возможно следует оптимизировать");
        if(m_parentNode) {
                m_position = inverse(m_parentNode->m_orientation * m_orientation)*d / (m_parentNode->m_scale*m_scale);
        }
}
