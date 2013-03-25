#include "AbstractLightSource.h"

AbstractLightSource::AbstractLightSource(const vec3 &ambientColor, const vec3 &diffuseColor, const vec3 &specularColor) {
        setAmbientColor(ambientColor);
        setDiffuseColor(diffuseColor);
        setSpecularColor(specularColor);
}
