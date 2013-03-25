#ifndef ABSTRACTLIGHTSOURCE_H
#define ABSTRACTLIGHTSOURCE_H

#include <glm/glm.hpp>

using namespace glm;

/** Абстрактный источник освещения.
  * Позволяет задать цвет источника света
  */
class AbstractLightSource {
private:
        vec3    m_ambientColor;
        vec3    m_diffuseColor;
        vec3    m_specularColor;

public:
        //Создает источник света с заданными цветом
        AbstractLightSource(const vec3& ambientColor=vec3(0.9), const vec3& diffuseColor=vec3(1.0,1.0,0.9),
                            const vec3& specularColor=vec3(1.0));

        //Установить/получить фоновый цвет
        const vec3&     ambientColor() const                                    { return m_ambientColor; }
        void            setAmbientColor(const vec3& color)                      { m_ambientColor = color; }

        //Установить/получить диффузный цвет
        const vec3&     diffuseColor() const                                    { return m_diffuseColor; }
        void            setDiffuseColor(const vec3& color)                      { m_diffuseColor = color; }

        //Установить/получить отражательный цвет
        const vec3&     specularColor() const                                   { return m_specularColor; }
        void            setSpecularColor(const vec3& color)                     { m_specularColor = color; }
};

#endif // ABSTRACTLIGHTSOURCE_H
