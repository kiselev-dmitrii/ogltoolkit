#include "SceneNode.h"
#include <glm/gtx/quaternion.hpp>
#include "lib/Utils/Debug.h"

void SceneNode::init() {
        m_orientation = quat(1,0,0,0);
        m_position = vec3(0);
        m_scale = vec3(1);

        m_orientationInWorld = quat(1,0,0,0);
        m_position = vec3(0);
        m_scale = vec3(1);

        m_isUpdateWorldValues = false;
}

void SceneNode::updateWorldValues() {
        if(m_isUpdateWorldValues) {
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

                m_isUpdateWorldValues = false;
        }

}

void SceneNode::notifyNeedToUpdateWorldValues() {
        m_isUpdateWorldValues = true;
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
        m_position = position;
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
        quat orientInParent = ((SceneNode*)m_parentNode)->convertWorldToLocal(orientation);
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
                m_position += (inverse(((SceneNode*)m_parentNode)->m_orientationInWorld) * delta) / ((SceneNode*)m_parentNode)->m_scaleInWorld;
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

void SceneNode::lookAt(const vec3 &target, const vec3 &up) {
        vec3 zAxis = normalize(-target);
        vec3 xAxis = normalize(cross(up, zAxis));
        vec3 yAxis = normalize(cross(zAxis, xAxis));

        mat3 matrix = mat3(xAxis.x, yAxis.x, zAxis.x,
                           xAxis.y, yAxis.y, zAxis.y,
                           xAxis.z, yAxis.z, zAxis.z);
        m_orientation = toQuat(matrix);
}

void SceneNode::updateLocalToWorldMatrix() {
        mat3 rot = toMat3(m_orientationInWorld);
        m_localToWorldMatrix = mat4(
                m_scaleInWorld.x*rot[0][0], m_scaleInWorld.y*rot[0][1], m_scaleInWorld.z*rot[0][2], m_positionInWorld.x,
                m_scaleInWorld.x*rot[1][0], m_scaleInWorld.y*rot[1][1], m_scaleInWorld.z*rot[1][2], m_positionInWorld.y,
                m_scaleInWorld.x*rot[2][0], m_scaleInWorld.y*rot[2][1], m_scaleInWorld.z*rot[2][2], m_positionInWorld.z,
                                        0 ,                         0 ,                         0 ,                   1
                );
}

const mat4& SceneNode::localToWorldMatrix() {
        if(m_isUpdateLocalToWorldMatrix) {
                updateLocalToWorldMatrix();
                m_isUpdateLocalToWorldMatrix = false;
        }

        return m_localToWorldMatrix;
}

const mat4& SceneNode::worldToLocalMatrix() {
        if(m_isUpdateLocalToWorldMatrix) {
                updateLocalToWorldMatrix();
                m_worldToLocalMatrix = inverse(m_localToWorldMatrix);
                m_isUpdateLocalToWorldMatrix = false;
        }
        return m_worldToLocalMatrix;
}

void SceneNode::onAddChild() {
        m_isUpdateWorldValues = true;
}

void SceneNode::onRemoveChild() {
        m_isUpdateWorldValues = true;
}
