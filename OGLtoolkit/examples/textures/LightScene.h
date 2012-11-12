#ifndef LIGHTSCENE_H
#define LIGHTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/Framework/Entity.h"
#include "lib/Framework/Camera.h"
#include "lib/Debug/Debug.h"
#include "lib/OGL/TextureUnit.h"
#include "lib/OGL/Texture2D.h"

class LightScene : public AbstractScene {
private:
        GpuProgram      *m_program;
        Camera          *m_camera;

        Entity          *m_plane;
        Entity          *m_box;
        TextureUnit     *m_tuBox;
        TextureUnit     *m_tuPlane;
        Texture2D       *m_texBrick;
        Texture2D       *m_texCement;


        void            setLightSource(int index, const vec3 &pos, const vec3 &amb, const vec3 &diff, const vec3 &spec);
public:
        LightScene();
        ~LightScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);
};

#endif // LIGHTSCENE_H
