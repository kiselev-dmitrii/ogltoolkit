#ifndef EDGETESTSCENE_H
#define EDGETESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/OGL/Framebuffer.h"
#include "lib/OGL/TextureUnit.h"

#include "lib/Framework/Camera.h"
#include "lib/Framework/Entity.h"

class BlurTestScene : public AbstractScene {
private:
        GpuProgram*     m_program;
        Camera*         m_camera;

        Entity*         m_ePlane;
        Entity*         m_eTeapot;
        Entity*         m_eMonkey;

        Framebuffer*    m_fbo1;
        Texture2D*      m_texture1;
        Texture2D*      m_depthTexture;

        Framebuffer*    m_fbo2;
        Texture2D*      m_texture2;
        Renderbuffer*   m_rbo2;

        TextureUnit*    m_sampler;
        TextureUnit*    m_depthSampler;

private:
        VertexArray*    m_vao;
        VertexBuffer*   m_vbo;
        IndexBuffer*    m_ibo;

        void            initQuad();
        void            drawQuad();

public:
        BlurTestScene();
        ~BlurTestScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    pass1();
        void    pass2();
        void    pass3();

        void    initRender();
        void    initTeapot();
        void    initPlane();
        void    initMonkey();

        void    renderTeapot();
        void    renderPlane();
        void    renderMonkey();
};

#endif // EDGETESTSCENE_H
