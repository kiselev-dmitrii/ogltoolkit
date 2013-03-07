#ifndef FRAMEWORKTEST_H
#define FRAMEWORKTEST_H

#include "lib/Core/OpenGL/GpuProgram.h"
#include "lib/Framework/AbstractScene.h"
#include "lib/Framework/EntityManager.h"
#include "lib/Framework/SceneNode.h"
#include "lib/Solutions/FirstPersonCamera.h"

class FrameWorkTest : public AbstractScene {
private:
        GpuProgram*             m_program;
        FirstPersonCamera*      m_camera;

        EntityManager*          m_entityManager;

        SceneNode*              m_cameraNode;
        SceneNode*              m_node1;
        SceneNode*              m_node2;
        SceneNode*              m_node3;

public:
        FrameWorkTest();
        ~FrameWorkTest();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    initRender();
        void    initEntities();
        void    initCamera();
        void    initShaders();
};

#endif // FRAMEWORKTEST_H
