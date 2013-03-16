#ifndef BOUNDBOX_H
#define BOUNDBOX_H

#include <glm/glm.hpp>
#include "lib/Framework/MeshInfo.h"

using namespace glm;

/** Параметрический BoundBox.
  * Создается, используется обход EntityManager.
  * Будет использоваться в основном в RenderManager.
*/
class BoundBox {
private:
        MeshInfo        m_meshInfo;

public:
        // Создает BoundBox между точками minCoords и maxCoords
        BoundBox(const vec3& minCoords, const vec3& maxCoords);

        // Изменяет размеры и положение BoundBox
        void            setGeometry(const vec3& minCoords, const vec3& maxCoords);

        // Возвращает указатель на MeshInfo
        MeshInfo*       meshInfo();
};

#endif // BOUNDBOX_H
