#ifndef LIGHTSCENE_H
#define LIGHTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/Framework/Entity.h"
#include "lib/Framework/Camera.h"

class LightScene : public AbstractScene {
private:
        Camera          *m_camera;
        Entity          *m_head;
        Entity          *m_box;

        GpuProgram      *m_program;

private:
        void    updateMatrix(Entity *entity);

public:
        LightScene();
        ~LightScene();

        void    init();
        void    resize(int w, int h);
        void    update(float t);
        void    render();
};

#endif // LIGHTSCENE_H
