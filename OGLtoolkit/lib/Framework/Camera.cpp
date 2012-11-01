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
}

void Camera::setProjectionType(ProjectionType::Enum type) {
        m_projType = type;
}

void Camera::setFarClipDistance(float distance) {
        m_farPlane = distance;
}

void Camera::setNearClipDistance(float distance) {
        m_nearPlane = distance;
}

void Camera::setAspectRatio(float ratio) {
        m_ratio = ratio;
}

void Camera::setFOV(float angle) {
        m_fovAngle = angle;
}

void Camera::setOrthoRect(float width, float height) {
        m_width = width;
        m_height = height;
}

void Camera::moveForward(float delta) {
        m_pos += delta*m_dir;
}

void Camera::moveRight(float delta) {
        vec3 right = glm::cross(m_dir, m_up);
        m_pos += delta*right;
}

void Camera::moveUp(float delta) {
        m_pos += delta*m_up;
}

void Camera::rotate(float angle, const vec3 &axis) {
        // При повороте будем менять лишь вектор m_dir
        m_dir = glm::rotate(m_dir, angle, axis);
}

void Camera::rotateWithMouse(const vec2 &delta) {
        vec2 angles = delta/20.0f;
        vec3 right = glm::cross(m_dir, m_up);
        rotate(angles.x, m_up);
        rotate(angles.y, right);
}

void Camera::setPosition(const vec3 &pos) {
        m_pos = pos;
}

void Camera::setTarget(const vec3 &target) {
        m_dir = glm::normalize(target-m_pos);
}

mat4* Camera::viewMatrix() {
        m_viewMatrix = glm::lookAt(m_pos, m_pos + m_dir, m_up);
        return &m_viewMatrix;
}

mat4* Camera::projectionMatrix() {
        switch (m_projType) {
                case ProjectionType::ORTHOGONAL:
                        m_projMatrix = glm::ortho(0.0f, m_width, 0.0f, m_height);
                        break;
                case ProjectionType::PERSPECTIVE:
                        m_projMatrix = glm::perspective(m_fovAngle, m_ratio, m_nearPlane, m_farPlane);
                        break;
        }
        return &m_projMatrix;
}
