#ifndef RENDER_H
#define RENDER_H

#include "Entity.h"
#include "AbstractCamera.h"
#include "lib/Core/OpenGL/GpuProgram.h"

/** Класс, для осуществления рендера
  */
class Render {
private:
        AbstractCamera* m_curCamera;
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
        void            setCurrentCamera(AbstractCamera *camera);
        AbstractCamera* currentCamera();

        // Занимается отрисовкой сущности
        void            render(Entity *entity);
};

#endif // RENDER_H
