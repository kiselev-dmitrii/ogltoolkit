#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtx/transform.hpp>
using glm::mat4;
using glm::vec3;
using namespace glm;



/** Класс камеры.
  * Позволяет удобно изменять положение, менять тип проекции, отсекающие плоскости и т.д
  * На самом деле изменяет только проекционную и видовую матрицу, которую затем можно получить,
  * используя методы: viewMatrix(), projectionMatrix()
  */
class Camera {
private:
        mat4    m_viewMatrix;
        mat4    m_projMatrix;
        bool    m_isViewMatrixChanged;
        bool    m_isProjMatrixChanged;

        vec3    m_dir;                  //ось, направленная вперед
        vec3    m_up;                   //ось, направленная вверх
        vec3    m_pos;                  //позиция камеры в мировой системе коорд.

        ProjectionType::Enum    m_projType;
        float                   m_nearPlane, m_farPlane;
        float                   m_ratio;
        float                   m_fovAngle;
        float                   m_width, m_height;

public:
        Camera();


        // Смещение по осям на значение delta
        void    moveForward(float delta);
        void    moveRight(float delta);
        void    moveUp(float delta);

        // Поворот на угол angle, относительно оси axis
        void    rotate(float angle, const vec3 &axis);
        // Поворачивает камеру, если мышь сместилась от центра, на величину delta
        void    rotateWithMouse(const vec2 &delta);

        // Установка позиции
        void    setPosition(const vec3 &pos);
        void    setTarget(const vec3 &target);
        // Получение позиции
        vec3    position();

        // Возвращает указатель на видовую матрицу
        mat4*   viewMatrix();
        // Возвращает указатель на проекционную матрицу
        mat4*   projectionMatrix();
};

#endif // CAMERA_H
