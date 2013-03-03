#ifndef ENTITY_H
#define ENTITY_H

#include "Movable.h"
#include <lib/Core/OpenGL/VertexArray.h>

/** Класс некоторой сущности.
  * Предстваляет собой меш, загруженный в видеопамять и доступный для рендеринга
  */
class Entity : public Movable {
private:
        VertexArray*    m_vertexArray;          //указатель на данные меша

public:
        // Создает объект с мешем, хрянящимся в vao
        Entity(VertexArray *vertexArray);

        // Возращает укащатель на vao
        VertexArray*    vertexArray() const;
};

#endif // ENTITY_H
