#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/Framework/Camera.h"
#include "lib/Framework/Entity.h"
#include "lib/OGL/TextureUnit.h"
#include "lib/OGL/Texture2D.h"

class TestScene : public AbstractScene {
private:
        GpuProgram*     m_normalMapping;
        Camera*         m_camera;

        Entity*         m_eOgre;
        Texture2D*      m_tOgre;
        Texture2D*      m_tOgreNormals;

        TextureUnit*    m_tuBase;
        TextureUnit*    m_tuNormalMap;

private:
        void    initRender();
        void    initLight();
        void    initOgreModel();
        void    renderOgreModel();

public:
        TestScene();
        ~TestScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);


};

#endif // TESTSCENE_H
