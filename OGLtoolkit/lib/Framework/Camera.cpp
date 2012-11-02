#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>
#include "lib/Debug/Debug.h"

Camera::Camera() {
        m_dir = vec3(1,0,0);
        m_up = vec3(0,0,1);
        m_pos = vec3(0,0,0);

        m_projType = ProjectionType::PERSPECTIVE;
        m_nearPlane = 0.05;
        m_farPlane = 100.0;
        m_ratio = 1.0;
        m_fovAngle = 30;
        m_width = m_height = 1.0;

        m_isViewMatrixChanged = true;
        m_isProjMatrixChanged = true;
}

void Camera::setProjectionType(ProjectionType::Enum type) {
        m_projType = type;
        m_isProjMatrixChanged = true;
}

void Camera::setFarClipDistance(float distance) {
        m_farPlane = distance;
        m_isProjMatrixChanged = true;
}

void Camera::setNearClipDistance(float distance) {
        m_nearPlane = distance;
        m_isProjMatrixChanged = true;
}

void Camera::setAspectRatio(float ratio) {
        m_ratio = ratio;
        m_isProjMatrixChanged = true;
}

void Camera::setFOV(float angle) {
        m_fovAngle = angle;
        m_isProjMatrixChanged = true;
}

void Camera::setOrthoRect(float width, float height) {
        m_width = width;
        m_height = height;
        m_isProjMatrixChanged = true;
}

void Camera::moveForward(float delta) {
        m_pos += delta*m_dir;
        m_isViewMatrixChanged = true;
}

void Camera::moveRight(float delta) {
        vec3 right = glm::cross(m_dir, m_up);
        m_pos += delta*right;
        m_isViewMatrixChanged = true;
}

void Camera::moveUp(float delta) {
        m_pos += delta*m_up;
        m_isViewMatrixChanged = true;
}

void Camera::rotate(float angle, const vec3 &axis) {
        // При повороте будем менять лишь вектор m_dir
        m_dir = glm::rotate(m_dir, angle, axis);
        m_isViewMatrixChanged = true;
}

void Camera::rotateWithMouse(const vec2 &delta) {
        vec2 angles = delta/20.0f;
        vec3 right = glm::cross(m_dir, m_up);
        rotate(angles.x, m_up);
        rotate(angles.y, right);
        m_isViewMatrixChanged = true;
}

void Camera::setPosition(const vec3 &pos) {
        m_pos = pos;
        m_isViewMatrixChanged = true;
}

void Camera::setTarget(const vec3 &target) {
        m_dir = glm::normalize(target-m_pos);
        m_isViewMatrixChanged = true;
}

mat4* Camera::viewMatrix() {
        if(m_isViewMatrixChanged) {
                m_viewMatrix = glm::lookAt(m_pos, m_pos + m_dir, m_up);
                m_isViewMatrixChanged = false;
        }

        return &m_viewMatrix;
}

mat4* Camera::projectionMatrix() {
        if(m_isProjMatrixChanged) {
                switch (m_projType) {
                        case ProjectionType::ORTHOGONAL:
                                m_projMatrix = glm::ortho(0.0f, m_width, 0.0f, m_height);
                                break;
                        case ProjectionType::PERSPECTIVE:
                                m_projMatrix = glm::perspective(m_fovAngle, m_ratio, m_nearPlane, m_farPlane);
                                break;
                }
                m_isProjMatrixChanged = false;
        }
        return &m_projMatrix;
}
