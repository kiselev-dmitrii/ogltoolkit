#ifndef EDGETESTSCENE_H
#define EDGETESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"

class EdgeTestScene : public AbstractScene {
public:
        EdgeTestScene();
        ~EdgeTestScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);

};

#endif // EDGETESTSCENE_H
