#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/OGL/TextureCube.h"
#include "lib/OGL/TextureUnit.h"
#include "lib/OGL/VertexBuffer.h"
#include "lib/OGL/IndexBuffer.h"
#include "lib/OGL/VertexArray.h"
#include "lib/OGL/Framebuffer.h"
#include "lib/OGL/Renderbuffer.h"

class TestScene : public AbstractScene {
private:
        GpuProgram*     m_cubemapProgram;

        TextureCube*    m_inputTexture;
        Texture2D*      m_outputPosX;
        Texture2D*      m_outputNegX;
        Texture2D*      m_outputPosY;
        Texture2D*      m_outputNegY;
        Texture2D*      m_outputPosZ;
        Texture2D*      m_outputNegZ;


        TextureUnit*    m_sampler;

        Framebuffer*    m_fbo;
        Renderbuffer*   m_rbo;


        VertexArray*    m_vao;
        VertexBuffer*   m_vbo;
        IndexBuffer*    m_ibo;

public:
        TestScene();
        ~TestScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    initQuad();
        void    drawQuad();
};

#endif // TESTSCENE_H
