#ifndef FRAMEWORKTEST_H
#define FRAMEWORKTEST_H

#include "lib/Framework/AbstractScene.h"
#include "lib/Framework/EntityManager.h"
#include "lib/Framework/RenderManager.h"
#include "lib/Framework/MeshManager.h"

#include "lib/Framework/SceneNode.h"
#include "lib/Solutions/FirstPersonCamera.h"

class FrameWorkTest : public AbstractScene {
private:
        EntityManager*          m_entityMgr;
        RenderManager*          m_renderMgr;
        MeshManager*            m_meshMgr;

        FirstPersonCamera*      m_camera;
        SceneNode*              m_cameraNode1;
        SceneNode*              m_cameraNode2;
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
