#include "Spotlight.h"

Spotlight::Spotlight(SceneNode *node, float angle, float distance) {
        setNode(node);
        setCutoffAngle(angle);
        setAttenuationDistance(distance);
}

void Spotlight::bindCamera(AbstractCamera *camera) {
        camera->setProjectionType(ProjectionType::PERSPECTIVE);
        camera->setNearClipDistance(0.01);
        camera->setFarClipDistance(m_cutoffAngle);
        camera->setFieldOfView(m_cutoffAngle);
        camera->setNode(m_node);

        m_camera = camera;
}
