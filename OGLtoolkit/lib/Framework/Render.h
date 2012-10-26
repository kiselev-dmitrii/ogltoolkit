#ifndef RENDER_H
#define RENDER_H

#include "Entity.h"

/** Синглтон для осуществления рендера
  */
class Render {
private:
        Render();
public:
        // Рендерит сущность
        void    render(Entity *entity);
};

#endif // RENDER_H
