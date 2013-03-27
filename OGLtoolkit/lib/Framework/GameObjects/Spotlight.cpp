#include "Spotlight.h"

Spotlight::Spotlight(SceneNode *node, float angle, float distance) {
        m_camera = NULL;
        setNode(node);
        setCutoffAngle(angle);
        setAttenuationDistance(distance);
}

void Spotlight::setCutoffAngle(float angle) {
        m_cutoffAngle = angle;
        if(m_camera) m_camera->setFieldOfView(m_cutoffAngle);
}

float Spotlight::cutoffAngle() const {
        return m_cutoffAngle;
}

void Spotlight::setAttenuationDistance(float distance) {
        m_attenuationDistance = distance;
        if(m_camera) m_camera->setFarClipDistance(m_attenuationDistance);
}

float Spotlight::attenuationDistance() const {
        return m_attenuationDistance;
}

void Spotlight::bindCamera(AbstractCamera *camera) {
        camera->setProjectionType(ProjectionType::PERSPECTIVE);
        camera->setNearClipDistance(0.01);
        camera->setFarClipDistance(m_attenuationDistance);
        camera->setFieldOfView(m_cutoffAngle);
        camera->setNode(m_node);

        m_camera = camera;
}
