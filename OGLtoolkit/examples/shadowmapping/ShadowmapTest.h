#ifndef FRAMEWORKTEST_H
#define FRAMEWORKTEST_H

#include "lib/Framework/AbstractScene.h"
#include "lib/Framework/EntityManager.h"
#include "lib/Framework/RenderManager.h"
#include "lib/Framework/MeshManager.h"
#include "lib/Framework/SceneManager.h"
#include "lib/Framework/TextureManager.h"
#include "lib/Framework/GameObjects/Spotlight.h"
#include "lib/Solutions/FirstPersonCamera.h"

#include "lib/Core/OpenGL/Framebuffer.h"
#include "lib/Core/OpenGL/TextureUnit.h"

class ShadowmapTest : public AbstractScene {
private:
        EntityManager*          m_entityMgr;
        RenderManager*          m_renderMgr;
        MeshManager*            m_meshMgr;
        TextureManager*         m_texMgr;
        SceneManager*           m_sceneMgr;

        SceneNode*              m_node1;
        SceneNode*              m_node2;
        SceneNode*              m_node3;
        SceneNode*              m_node4;

        FirstPersonCamera*      m_mainCamera;
        Spotlight*              m_spot;

private:
        // Это уйдет в RenderManager
        MeshInfo*               m_quad;
        Framebuffer*            m_fbo;
        TextureUnit*            m_tu;

        void                    pass1();
        void                    pass2();
        void                    initFBO();
        void                    showShadowMap();

public:
        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    initEntities();
        void    initCamera();
        void    initShaders();
        void    initLight();
};

/** Техника затененения ShadowMapping
  */
class ShadowMapping {
public:

};

#endif // FRAMEWORKTEST_H
