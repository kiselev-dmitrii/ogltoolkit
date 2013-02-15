#ifndef IMAGELIGHTINGSCENE_H
#define IMAGELIGHTINGSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/OGL/TextureCube.h"
#include "lib/OGL/TextureUnit.h"
#include "lib/Framework/Camera.h"
#include "lib/Framework/Entity.h"

class ImageLightingScene : public AbstractScene {
private:
        GpuProgram*     m_iblLighting;
        GpuProgram*     m_renderCubemap;
        GpuProgram*     m_renderGlass;

        Camera*         m_camera;

        TextureCube*    m_tcRoom;
        TextureCube*    m_tcDiffuseRoom;
        TextureCube*    m_tcSpecularRoom;

        TextureUnit*    m_tuBase;
        TextureUnit*    m_tuDiffuse;
        TextureUnit*    m_tuSpecular;

        Entity*         m_eTeapot;
        Entity*         m_eSkybox;

public:
        ImageLightingScene();
        ~ImageLightingScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    initRender();
        void    initTeapot();
        void    initSkybox();

        void    renderTeapot();
        void    renderSkybox();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);

};

#endif // IMAGELIGHTINGSCENE_H
