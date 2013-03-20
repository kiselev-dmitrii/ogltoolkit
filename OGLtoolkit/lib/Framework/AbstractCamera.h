#ifndef ABSTRACTCAMERA_H
#define ABSTRACTCAMERA_H

#include "ViewFrustum.h"
#include "Movable.h"

/** Определяет основные методы для работы с камерой.
  * Данный класс должен быть наследован уже в конкретном приложении, для связи
  * камеры с устройствами ввода.
  */
class AbstractCamera : public ViewFrustum, public Movable {
public:
        // Создает камеру, подключенную к узлу node
        AbstractCamera(SceneNode* node);
        // Виртуальный деструктор
        virtual         ~AbstractCamera()                                               {}

        // Перемещает камеру вперед/вправо/вверх на расстояние delta
        void            moveForward(float delta);
        void            moveRight(float delta);
        void            moveUp(float delta);

        // Вращает камеру так, если курсор передвинется от центра на вектор delta
        void            rotateWithMouse(const vec2& angles);

public:
        // Переопределяется в наследуемых классах.
        // Определяет, как камера будет реагировать на нажатия клавиш
        virtual void    update(float deltaTime) = 0;

};

#endif // ABSTRACTCAMERA_H
