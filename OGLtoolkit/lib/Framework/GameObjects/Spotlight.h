#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "lib/Framework/AbstractCamera.h"
#include "lib/Framework/Movable.h"
#include "lib/Framework/SceneNode.h"
#include "AbstractLightSource.h"

/** Источник освещения типа прожеткор
  * Имеет направление и конус освещения
  */
class Spotlight : public AbstractLightSource, public Movable {
private:
        float           m_cutoffAngle;          //угол развертки конуса проектора
        float           m_attenuationDistance;  //высота конуса проектора (за конусом предметы не освещены)

        AbstractCamera* m_camera;
public:
        //Создает проектор с углом развертки angle и осветительным расстоянием distance
        Spotlight(SceneNode* node, float angle=90.0f, float distance=1000.0f);

        //Устанавливает/возвращает угол развертки
        void            setCutoffAngle(float angle)                     { m_cutoffAngle = angle; }
        float           cutoffAngle() const                             { return m_cutoffAngle; }

        //Устанавливает/возвращает осветительное расстояние
        void            setAttenuationDistance(float distance)          { m_attenuationDistance = distance; }
        float           attenuationDistance() const                     { return m_attenuationDistance; }

        // Привязывает камеру к проектору. Таким образом он видит все что проектор
        void            bindCamera(AbstractCamera* camera);
        AbstractCamera* camera()                                        { return m_camera; }

};

#endif // SPOTLIGHT_H
