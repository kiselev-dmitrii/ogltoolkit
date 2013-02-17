#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "lib/OGL/AbstractScene.h"
#include "lib/OGL/GpuProgram.h"
#include "lib/OGL/Texture2D.h"
#include "lib/OGL/TextureUnit.h"

#include "lib/Framework/Camera.h"
#include "lib/Framework/Entity.h"

class TestScene : public AbstractScene {
private:
        GpuProgram*     m_projector;
        Camera*         m_camera;

        Texture2D*      m_tLogo;
        TextureUnit*    m_tuProjTexture;

        Entity*         m_ePlane;
        Entity*         m_eTeapot;


        // Возвращает матрицу, которая переводит мировые координаты в координаты проектора
        mat4            calcProjectorMatrix(const vec3& pos, const vec3& dir, const vec3& up);
public:
        TestScene();
        ~TestScene();

        void    init();
        void    resize(int w, int h);
        void    update(float deltaTime);
        void    render();

        void    initRender();
        void    initTeapot();
        void    initPlane();

        void    renderTeapot();
        void    renderPlane();

public:
        void    onKeyPress(int key);
        void    onMouseMove(int x, int y);

};

#endif // TESTSCENE_H
