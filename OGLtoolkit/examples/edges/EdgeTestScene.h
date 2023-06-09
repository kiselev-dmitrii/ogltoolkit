#ifndef EDGETESTSCENE_H
#define EDGETESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/OGL/Framebuffer.h"
#include "lib/OGL/TextureUnit.h"

#include "lib/Framework/Camera.h"
#include "lib/Framework/Entity.h"

class EdgeTestScene : public AbstractScene {
private:
        GpuProgram*     m_program;
        Camera*         m_camera;

        Entity*         m_ePlane;
        Entity*         m_eTeapot;

        Framebuffer*    m_fbo;
        Texture2D*      m_texture;
        TextureUnit*    m_sampler;
        Renderbuffer*   m_rbo;

        string          m_secondPass;

private:
        VertexArray*    m_vao;
        VertexBuffer*   m_vbo;
        IndexBuffer*    m_ibo;

        void            initQuad();
        void            drawQuad();

public:
        EdgeTestScene();
        ~EdgeTestScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    pass1();
        void    pass2();

        void    initRender();
        void    initTeapot();
        void    initPlane();

        void    renderTeapot();
        void    renderPlane();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);

};

#endif // EDGETESTSCENE_H
