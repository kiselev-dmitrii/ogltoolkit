#ifndef TRIANGLESCENE_H
#define TRIANGLESCENE_H

#include <GL/glew.h>
#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/OGL/VertexBuffer.h"
#include "lib/OGL/VertexArray.h"
#include "lib/OGL/UniformBuffer.h"
#include "lib/OGL/IndexBuffer.h"

class TriangleScene : public AbstractScene {
private:
        GpuProgram*     m_program;
        VertexArray*    m_vao;
        VertexBuffer*   m_vboPositions;
        VertexBuffer*   m_vboTexCoord;
        IndexBuffer*    m_ibo;
        UniformBuffer*  m_uboBlobSettings;

        UniformBlock*   m_blobSettigs;
public:
        TriangleScene();
        ~TriangleScene();

        virtual void init();
        virtual void resize(int w, int h);
        virtual void update(float t);
        virtual void render();
};

#endif // TRIANGLESCENE_H
