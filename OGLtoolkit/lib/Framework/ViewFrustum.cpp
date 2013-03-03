#include "ViewFrustum.h"
#include <glm/gtx/transform.hpp>

ViewFrustum::ViewFrustum() { }

void ViewFrustum::setProjectionType(ProjectionType::Enum type) {
        m_projType = type;
        m_isUpdateMatrix = true;
}

ProjectionType::Enum ViewFrustum::projectionType() const {
        return m_projType;
}

void ViewFrustum::setFarClipDistance(float distance) {
        m_farClipDist = distance;
        m_isUpdateMatrix = true;
}

float ViewFrustum::farClipDistance() const {
        return m_farClipDist;
}

void ViewFrustum::setNearClipDistance(float distance) {
        m_nearClipDist = distance;
        m_isUpdateMatrix = true;
}

float ViewFrustum::nearClipDistance() const {
        return m_nearClipDist;
}

void ViewFrustum::setAspectRatio(float ratio) {
        m_aspectRatio = ratio;
        m_isUpdateMatrix = true;
}

float ViewFrustum::aspectRatio() const {
        return m_aspectRatio;
}

void ViewFrustum::setFieldOfView(float angle) {
        m_fieldOfView = angle;
        m_isUpdateMatrix = true;
}

float ViewFrustum::fieldOfView() const {
        return m_fieldOfView;
}

void ViewFrustum::setOrthoRect(const vec2 &rect) {
        m_orthoRect = rect;
        m_isUpdateMatrix = true;
}

vec2 ViewFrustum::orthoRect() const {
        return m_orthoRect;
}

const mat4& ViewFrustum::viewToScreenMatrix() {
        if(m_isUpdateMatrix) {
                switch(m_projType) {
                        case ProjectionType::ORTHOGONAL:
                                m_viewToScreenMatrix = glm::ortho(0.0f, m_orthoRect.x, 0.0f, m_orthoRect.y);
                                break;
                        case ProjectionType::PERSPECTIVE:
                                m_viewToScreenMatrix = glm::perspective(m_fieldOfView, m_aspectRatio, m_nearClipDist, m_farClipDist);
                                break;
                }
                m_isUpdateMatrix = false;
        }

        return m_viewToScreenMatrix;
}
