#ifndef FRAMEWORKTEST_H
#define FRAMEWORKTEST_H

#include "lib/Framework/AbstractScene.h"
#include "lib/Framework/EntityManager.h"
#include "lib/Framework/RenderManager.h"
#include "lib/Framework/MeshManager.h"
#include "lib/Framework/SceneManager.h"


class ShadowmapTest : public AbstractScene {
private:
        EntityManager*          m_entityMgr;
        RenderManager*          m_renderMgr;
        MeshManager*            m_meshMgr;
        SceneManager*           m_sceneMgr;

        SceneNode*              m_node1;
        SceneNode*              m_node2;
        SceneNode*              m_node3;
        SceneNode*              m_node4;

public:
        ShadowmapTest();
        ~ShadowmapTest();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    initRender();
        void    initEntities();
        void    initCamera();
        void    initShaders();
};

/** Техника затененения ShadowMapping
  */
class ShadowMapping {
public:

};

#endif // FRAMEWORKTEST_H
