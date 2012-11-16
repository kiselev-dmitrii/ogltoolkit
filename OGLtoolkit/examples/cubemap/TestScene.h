#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/Framework/Camera.h"
#include "lib/Framework/Entity.h"
#include "lib/OGL/TextureUnit.h"
#include "lib/OGL/TextureCube.h"

class TestScene : public AbstractScene {
private:
        GpuProgram*     m_reflection;
        Camera*         m_camera;

        Entity*         m_eTeapot;
        Entity*         m_eSkybox;
        TextureCube*    m_tcEnvironment;


        TextureUnit*    m_tuCubeMap;

private:
        void    initRender();
        void    initSkybox();
        void    initTeapotModel();
        void    renderTeapotModel();
        void    renderSkybox();

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
