#ifndef VIEWFRUSTUM_H
#define VIEWFRUSTUM_H

#include <glm/glm.hpp>
using glm::mat4;
using namespace glm;

/** Тип проеции
  */
namespace ProjectionType {
enum Enum {
        PERSPECTIVE,            //перспективная проекция
        ORTHOGONAL              //ортогональная проекция
};
}

/** Класс представляет собой средство для настройки области видимости.
  * Результатом настройки пирамиды видимости является матрица проекции,
  * которая переводит view space в clip space.
  *
  * Может наследоваться камерой, или чем-то, что может иметь матрицу проекции,
  * например иногда требуется при освещении.
  */
class ViewFrustum {
private:
        mat4    m_viewToScreenMatrix;   //матрица проекции
        bool    m_isUpdateMatrix;       //нужно обновить матрицу проекции

        ProjectionType::Enum    m_projType;
        float                   m_nearClipDist;
        float                   m_farClipDist;
        float                   m_aspectRatio;
        float                   m_fieldOfView;
        vec2                    m_orthoRect;

public:
        // Конструктор. Задает параметры по умолчанию
        ViewFrustum();

        // Устанавливает/возвращает тип проекции
        void                    setProjectionType(ProjectionType::Enum type);
        ProjectionType::Enum    projectionType() const;

        // Устанавливает/возвращает расстояние до дальней отсекающей плоскости
        void                    setFarClipDistance(float distance);
        float                   farClipDistance() const;

        // Устанавливает/возвращает расстояние до ближней отсекающей плоскости
        void                    setNearClipDistance(float distance);
        float                   nearClipDistance() const;

        // Устанавливает/возвращает соотношение сторон
        void                    setAspectRatio(float ratio);
        float                   aspectRatio() const;

        // Уставливает/возвращает угол обзора
        void                    setFieldOfView(float angle);
        float                   fieldOfView() const;

        // Уставливает ширину и высоту прямогольника при ортогональной проекции
        void                    setOrthoRect(const vec2& rect);
        vec2                    orthoRect() const;

        // Возвращает матрицу перехода из видовых координат в экранные (матрицу проекции)
        const mat4&             viewToScreenMatrix();

};

#endif // VIEWFRUSTUM_H
