#ifndef LIGHTSCENE_H
#define LIGHTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/VertexBuffer.h"
#include "lib/OGL/VertexArray.h"
#include "lib/OGL/IndexBuffer.h"
#include "lib/Data/Mesh.h"
#include "lib/OGL/GpuProgram.h"

class LightScene : public AbstractScene {
private:
        Mesh            *m_mesh;
        VertexBuffer    *m_vboMesh;
        IndexBuffer     *m_iboMesh;
        VertexArray     *m_vaoMesh;

        GpuProgram      *m_program;
public:
        LightScene();
        ~LightScene();

        void    init();
        void    resize(int w, int h);
        void    update(float t);
        void    render();
};

#endif // LIGHTSCENE_H
