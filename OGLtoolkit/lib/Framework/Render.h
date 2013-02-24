#ifndef RENDER_H
#define RENDER_H

#include "Entity.h"
#include "Camera.h"
#include "lib/Core/OpenGL/GpuProgram.h"

/** Класс, для осуществления рендера
  */
class Render {
private:
        Camera*         m_curCamera;
        GpuProgram*     m_curProgram;

private:
        // Отправляет матрицы в шейдер
        void            updateMatrices(Camera *camera, Entity *entity);

        // Закрытый конструктор для синглтона
        Render() {}

public:
        // Точка доступа к объекту
        static Render*  instance();

        // Установка/получение текущей шейдерной программы
        void            setCurrentProgram(GpuProgram *program);
        GpuProgram*     currentProgram();

        // Установка/получение текущей камеры
        void            setCurrentCamera(Camera *camera);
        Camera*         currentCamera();

        // Занимается отрисовкой сущности
        void            render(Entity *entity);
};

#endif // RENDER_H
