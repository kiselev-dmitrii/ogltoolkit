#ifndef FBOTESTSCENE_H
#define FBOTESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/OGL/Texture2D.h"
#include "lib/OGL/TextureUnit.h"
#include "lib/OGL/Renderbuffer.h"
#include "lib/OGL/Framebuffer.h"

#include "lib/Framework/Camera.h"
#include "lib/Framework/Entity.h"

class FBOTestScene : public AbstractScene {
private:
        GpuProgram*     m_lightingProgram;
        Camera*         m_camera;

        Entity*         m_eTeapot;
        Entity*         m_eBox;
        TextureUnit*    m_tuBoxCover;

        Texture2D*      m_tColorBuff;
        Renderbuffer*   m_rbDepthBuff;
        Framebuffer*    m_fbo;

        Texture2D*      m_brickTexture;

public:
        FBOTestScene();
        ~FBOTestScene();


        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    initRender();
        void    initBox();
        void    initTeapot();

        void    renderBox();
        void    renderTeapot();

        void    renderTeapotFromView();
        void    renderToTexture();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);

};

#endif // FBOTESTSCENE_H
