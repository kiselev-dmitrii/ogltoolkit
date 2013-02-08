#ifndef %SCENE_NAME_UPPER%_H
#define %SCENE_NAME_UPPER%_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"

class %SCENE_NAME% : public AbstractScene {
public:
        %SCENE_NAME%();
        ~%SCENE_NAME%();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);

};

#endif // %SCENE_NAME_UPPER%_H
