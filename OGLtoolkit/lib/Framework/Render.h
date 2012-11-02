#ifndef RENDER_H
#define RENDER_H

#include "Entity.h"

/** Статический класс, для осуществления рендера
  */
class Render {
public:
        // Занимается отрисовкой сущности
        static void     render(Entity *entity);
};

#endif // RENDER_H
