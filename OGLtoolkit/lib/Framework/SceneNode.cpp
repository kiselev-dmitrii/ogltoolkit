#include "SceneNode.h"

void SceneNode::init() {
        m_orientation = quat(1,0,0,0);
        m_position = vec3(0);
        m_scale = vec3(1);

        m_orientationInWorld = quat(1,0,0,0);
        m_position = vec3(0);
        m_scale = vec3(1);

        m_isNeedToUpdate = false;
}

void SceneNode::update() {
        if(m_isNeedToUpdate) {
                if (m_parentNode) {
                        vec3 parentWorldPos = ((SceneNode*) m_parentNode)->positionInWorld();
                        quat parentWorldOrient = ((SceneNode*) m_parentNode)->orientationInWorld();
                        vec3 parentWorldScale = ((SceneNode*) m_parentNode)->scaleInWorld();

                        m_positionInWorld = parentWorldOrient * (parentWorldScale * m_position) + parentWorldPos;
                        m_orientationInWorld = parentWorldOrient * m_orientation;
                        m_scaleInWorld = parentWorldScale * m_scale;

                } else {
                        m_positionInWorld = m_position;
                        m_orientationInWorld = m_orientation;
                        m_scaleInWorld = m_scale;
                }

                m_isNeedToUpdate = false;
        }

}

SceneNode::SceneNode() : TreeNode() {
        init();
}

SceneNode::SceneNode(const string &name) : TreeNode(name) {
        init();
}

SceneNode::~SceneNode() {
        TODO;
}

const vec3& SceneNode::positionInWorld() {
        update();
        return m_positionInWorld;
}

const quat& SceneNode::orientationInWorld() {
        update();
        return m_orientationInWorld;
}

const vec3& SceneNode::scaleInWorld() {
        update();
        return m_scaleInWorld;
}

void SceneNode::onAddChild() {
        m_isNeedToUpdate = true;
}

void SceneNode::onRemoveChild() {
        m_isNeedToUpdate = true;
}
