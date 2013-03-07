#include "AbstractCamera.h"

AbstractCamera::AbstractCamera(SceneNode *node) : ViewFrustum(), Movable(node) { }

void AbstractCamera::moveForward(float delta) {
        m_node->translateInLocal(vec3(0,0,-delta));
}

void AbstractCamera::moveRight(float delta) {
        m_node->translateInLocal(vec3(delta,0,0));
}

void AbstractCamera::moveUp(float delta) {
        m_node->translateInLocal(vec3(0,delta,0));
}

void AbstractCamera::rotateWithMouse(const vec2 &angles) {
        m_node->rotateInParent(vec3(0,0,1), angles.x);
        m_node->rotateInLocal(vec3(1,0,0), angles.y);
}
