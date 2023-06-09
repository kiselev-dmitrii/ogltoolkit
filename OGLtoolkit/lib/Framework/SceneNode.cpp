#include "SceneNode.h"
#include <glm/gtx/quaternion.hpp>
#include "lib/Utils/Debug.h"

void SceneNode::init() {
        m_orientation = quat(1,0,0,0);
        m_position = vec3(0);
        m_scale = vec3(1);

        m_orientationInWorld = quat(1,0,0,0);
        m_positionInWorld = vec3(0);
        m_scaleInWorld = vec3(1);

        notifyChilds();
}

void SceneNode::updateWorldCoords() {
        if(m_isUpdateWorldCoords) {
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

                m_isUpdateWorldCoords = false;
        }
}

void SceneNode::notifyChilds() {
        m_isUpdateWorldCoords = true;
        m_isUpdateLocalToWorld = true;
        m_isUpdateWorldToLocal = true;

        NodeMap::iterator it;
        for(it=m_childNodes.begin(); it!=m_childNodes.end(); ++it) {
                ((SceneNode* )it->second)->notifyChilds();
        }
}

void SceneNode::updateLocalToWorldMatrix() {
        if(m_isUpdateLocalToWorld) {
                updateWorldCoords();

                mat3 rot = toMat3(m_orientationInWorld);

                m_localToWorldMatrix = mat4(
                        m_scaleInWorld.x*rot[0][0], m_scaleInWorld.y*rot[0][1], m_scaleInWorld.z*rot[0][2], 0,
                        m_scaleInWorld.x*rot[1][0], m_scaleInWorld.y*rot[1][1], m_scaleInWorld.z*rot[1][2], 0,
                        m_scaleInWorld.x*rot[2][0], m_scaleInWorld.y*rot[2][1], m_scaleInWorld.z*rot[2][2], 0,
                        m_positionInWorld.x       , m_positionInWorld.y       , m_positionInWorld.z       , 1 );

                m_isUpdateLocalToWorld = false;
        }
}

void SceneNode::updateWorldToLocalMatrix() {
        if(m_isUpdateWorldToLocal) {
                updateLocalToWorldMatrix();
                m_worldToLocalMatrix = inverse(m_localToWorldMatrix);

                m_isUpdateWorldToLocal = false;
        }
}

SceneNode::SceneNode() : TreeNode() {
        init();
}

SceneNode::SceneNode(const string &name) : TreeNode(name) {
        init();
}

SceneNode::~SceneNode() {
}

SceneNode* SceneNode::createChildNode(const string &name) {
        SceneNode* node = new SceneNode(name);
        this->addChildNode(node);
        return node;
}

vec3 SceneNode::convertWorldToLocal(const vec3 &worldVec) {
        updateWorldCoords();
        return inverse(m_orientationInWorld) * (worldVec - m_positionInWorld) / m_scaleInWorld;
}

quat SceneNode::convertWorldToLocal(const quat &worldQuat) {
        updateWorldCoords();
        return inverse(m_orientationInWorld) * worldQuat;
}

vec3 SceneNode::convertLocalToWorld(const vec3 &localVec) {
        updateWorldCoords();
        return (m_orientationInWorld * (localVec * m_scaleInWorld)) + m_positionInWorld;
}

quat SceneNode::convertLocalToWorld(const quat &localQuat) {
        updateWorldCoords();
        return m_orientationInWorld * localQuat;
}

void SceneNode::setPositionInParent(const vec3 &position) {
        m_position = position;
        notifyChilds();
}

void SceneNode::setOrientationInParent(const quat &orientation) {
        m_orientation = orientation;
        notifyChilds();
}

void SceneNode::setScaleInParent(const vec3 &scale) {
        m_scale = scale;
        notifyChilds();
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
        if(m_parentNode) {
                vec3 posInParent = ((SceneNode*)m_parentNode)->convertWorldToLocal(position);
                setPositionInParent(posInParent);
        } else {
                setPositionInParent(position);
        }
}

void SceneNode::setOrientationInWorld(const quat &orientation) {
        if(m_parentNode) {
                quat orientInParent = ((SceneNode*)m_parentNode)->convertWorldToLocal(orientation);
                setOrientationInParent(orientInParent);
        } else {
                setOrientationInParent(orientation);
        }
}

void SceneNode::setScaleInWorld(const vec3 &scale) {
        if(m_parentNode) {
                vec3 scaleInParent = ((SceneNode*)m_parentNode)->convertWorldToLocal(scale);
                setScaleInParent(scaleInParent);
        } else {
                setScaleInParent(scale);
        }
}

const vec3& SceneNode::positionInWorld() {
        updateWorldCoords();
        return m_positionInWorld;
}

const quat& SceneNode::orientationInWorld() {
        updateWorldCoords();
        return m_orientationInWorld;
}

const vec3& SceneNode::scaleInWorld() {
        updateWorldCoords();
        return m_scaleInWorld;
}

void SceneNode::translateInLocal(const vec3 &delta) {
        m_position += m_orientation * delta;
        notifyChilds();
}

void SceneNode::translateInParent(const vec3 &delta) {
        m_position += delta;
        notifyChilds();
}

void SceneNode::translateInWorld(const vec3 &delta) {
        if (m_parentNode) {
                ((SceneNode*)m_parentNode)->updateWorldCoords();
                m_position += (inverse(((SceneNode*)m_parentNode)->m_orientationInWorld) * delta) / ((SceneNode*)m_parentNode)->m_scaleInWorld;
        } else {
                m_position += delta;
        }
        notifyChilds();
}

void SceneNode::rotateInLocal(const quat &quaternion) {
        m_orientation = m_orientation * normalize(quaternion);
        notifyChilds();
}

void SceneNode::rotateInParent(const quat &quaternion) {
        m_orientation = normalize(quaternion) * m_orientation;
        notifyChilds();
}

void SceneNode::rotateInWorld(const quat &quaternion) {
        updateWorldCoords();
        m_orientation = m_orientation * inverse(m_orientationInWorld) * normalize(quaternion) * m_orientationInWorld;
        notifyChilds();
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

void SceneNode::lookAt(const vec3 &targetInWorld, const vec3 &upInParent) {
        vec3 targetInParent;
        if(m_parentNode) targetInParent = ((SceneNode*)m_parentNode)->convertWorldToLocal(targetInWorld);
        else targetInParent = targetInWorld;

        vec3 zAxis = -normalize(targetInParent-positionInParent());
        vec3 xAxis = normalize(cross(upInParent, zAxis));
        vec3 yAxis = normalize(cross(zAxis, xAxis));

        mat3 matrix = mat3(xAxis.x, xAxis.y, xAxis.z,
                           yAxis.x, yAxis.y, yAxis.z,
                           zAxis.x, zAxis.y, zAxis.z);
        setOrientationInParent(toQuat(matrix));
}


const mat4& SceneNode::localToWorldMatrix() {
        updateLocalToWorldMatrix();
        return m_localToWorldMatrix;
}

const mat4& SceneNode::worldToLocalMatrix() {
        updateWorldToLocalMatrix();
        return m_worldToLocalMatrix;
}

void SceneNode::onAddChild() {
        notifyChilds();
}

void SceneNode::onRemoveChild() {
        notifyChilds();
}
