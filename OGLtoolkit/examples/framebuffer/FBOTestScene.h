#ifndef FBOTESTSCENE_H
#define FBOTESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"

class FBOTestScene : public AbstractScene {
public:
        FBOTestScene();
        ~FBOTestScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);

};

#endif // FBOTESTSCENE_H
