#include "SceneNode.h"

void SceneNode::init() {
        m_orientation = quat(1,0,0,0);
        m_position = vec3(0);
        m_scale = vec3(1);

        m_orientationInWorld = quat(1,0,0,0);
        m_position = vec3(0);
        m_scale = vec3(1);

        m_isNeedToUpdateWorldValues = false;
}

void SceneNode::updateWorldValues() {
        if(m_isNeedToUpdateWorldValues) {
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

                m_isNeedToUpdateWorldValues = false;
        }

}

void SceneNode::notifyNeedToUpdateWorldValues() {
        m_isNeedToUpdateWorldValues = true;
        NodeMap::iterator it;
        for(it=m_childNodes.begin(); it!=m_childNodes.end(); ++it) {
                ((SceneNode* )it->second)->notifyNeedToUpdateWorldValues();
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

vec3 SceneNode::convertWorldToLocal(const vec3 &worldVec) {
        updateWorldValues();
        return inverse(m_orientationInWorld) * (worldVec - m_positionInWorld) / m_scaleInWorld;
}

quat SceneNode::convertWorldToLocal(const quat &worldQuat) {
        updateWorldValues();
        return inverse(m_orientationInWorld) * worldQuat;
}

vec3 SceneNode::convertLocalToWorld(const vec3 &localVec) {
        updateWorldValues();
        return (m_orientationInWorld * (localVec * m_scaleInWorld)) + m_positionInWorld;
}

quat SceneNode::convertLocalToWorld(const quat &localQuat) {
        updateWorldValues();
        return m_orientationInWorld * localQuat;
}

void SceneNode::setPositionInParent(const vec3 &position) {
        m_position = pos;
        notifyNeedToUpdateWorldValues();
}

void SceneNode::setOrientationInParent(const quat &orientation) {
        m_orientation = orientation;
        notifyNeedToUpdateWorldValues();
}

void SceneNode::setScaleInParent(const vec3 &scale) {
        m_scale = scale;
        notifyNeedToUpdateWorldValues();
}

const vec3& SceneNode::positionInParent() {
        return m_position;
}

const quat& SceneNode::orientationInParent() {
        return m_orientation;
}

const vec3& SceneNode::scaleInParent() {
        return m_scale;
}

void SceneNode::setPositionInWorld(const vec3 &position) {
        vec3 posInParent = ((SceneNode*)m_parentNode)->convertWorldToLocal(position);
        setPositionInParent(posInParent);
}

void SceneNode::setOrientationInWorld(const quat &orientation) {
        vec3 orientInParent = ((SceneNode*)m_parentNode)->convertWorldToLocal(orientation);
        setOrientationInParent(orientInParent);
}

void SceneNode::setScaleInWorld(const vec3 &scale) {
        TODO;
}

const vec3& SceneNode::positionInWorld() {
        updateWorldValues();
        return m_positionInWorld;
}

const quat& SceneNode::orientationInWorld() {
        updateWorldValues();
        return m_orientationInWorld;
}

const vec3& SceneNode::scaleInWorld() {
        updateWorldValues();
        return m_scaleInWorld;
}

void SceneNode::translateInLocal(const vec3 &delta) {
        m_position += m_orientation * delta;
        notifyNeedToUpdateWorldValues();
}

void SceneNode::translateInParent(const vec3 &delta) {
        m_position += delta;
        notifyNeedToUpdateWorldValues();
}

void SceneNode::translateInWorld(const vec3 &delta) {
        if (m_parentNode) {
                m_position += (inverse(((SceneNode*)m_parentNode)->m_positionInWorld) * delta) / ((SceneNode*)m_parentNode)->m_scaleInWorld;
        } else {
                m_position += delta;
        }
        notifyNeedToUpdateWorldValues();
}

void SceneNode::rotateInLocal(const quat &quaternion) {
        m_orientation = m_orientation * normalize(quaternion);
        notifyNeedToUpdateWorldValues();
}

void SceneNode::rotateInParent(const quat &quaternion) {
        m_orientation = normalize(quaternion) * m_orientation;
        notifyNeedToUpdateWorldValues();
}

void SceneNode::rotateInWorld(const quat &quaternion) {
        m_orientation = m_orientation * inverse(m_orientationInWorld) * normalize(quaternion) * m_orientationInWorld;
        notifyNeedToUpdateWorldValues();
}

void SceneNode::rotateInLocal(const vec3 &axis, float angle) {
        quat q = angleAxis(angle, axis);
        rotateInLocal(q);
}

void SceneNode::rotateInParent(const vec3 &axis, float angle) {
        quat q = angleAxis(angle, axis);
        rotateInParent(q);
}

void SceneNode::rotateInWorld(const vec3 &axis, float angle) {
        quat q = angleAxis(angle, axis);
        rotateInWorld(q);
}

void SceneNode::onAddChild() {
        m_isNeedToUpdateWorldValues = true;
}

void SceneNode::onRemoveChild() {
        m_isNeedToUpdateWorldValues = true;
}
