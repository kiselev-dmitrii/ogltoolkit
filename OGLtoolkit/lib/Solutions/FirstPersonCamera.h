#ifndef FIRSTPERSONCAMERA_H
#define FIRSTPERSONCAMERA_H

#include "lib/Framework/AbstractCamera.h"

/** Камера, которая используется в First Person Shooter
  * Вращание происходит так, как в большинстве шутеров
  */
class FirstPersonCamera : public AbstractCamera {
private:
        // Чувствительность мыши от 0.0 до 100
        float   m_mouseSensitivity;
        // Скорость перемещения
        float   m_speedMovement;

private:
        // Обновление ориентации
        void    updateOrientation(float deltaTime);
        // Обновление позиции
        void    updatePosition(float deltaTime);

public:
        // Конструктор
        FirstPersonCamera(SceneNode* node);

        // Установка чуствительности камеры при повороте
        void    setMouseSensitivity(float sensitivity);
        float   mouseSensitivity() const;

        // Установка скорости движения камеры
        void    setSpeedOfMovement(float speed);
        float   speedOfMovement() const;

        // Метод обновления позиции и ориентации камеры
        void    update(float deltaTime);
};

#endif // DEFAULTCAMERA_H
