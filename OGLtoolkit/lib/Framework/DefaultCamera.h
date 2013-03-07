#ifndef DEFAULTCAMERA_H
#define DEFAULTCAMERA_H

#include "AbstractCamera.h"

/** Камера, которая будет использоваться в большинстве случаев.
  * Скорее всего, следует перенести эту камеру на другой уровень (например GameObjects),
  * т.к. она использует классы из Subsystems (устройства ввода и доступ к окну)
  */
class DefaultCamera : public AbstractCamera {
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
        DefaultCamera(SceneNode* node);

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
