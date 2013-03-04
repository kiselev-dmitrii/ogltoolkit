#ifndef ENTITY_H
#define ENTITY_H

#include "Movable.h"

struct MeshInfo;

/** Класс некоторой сущности.
  * Предстваляет собой меш, загруженный в видеопамять и доступный для рендеринга
  */
class Entity : public Movable {
private:
        MeshInfo*       m_meshInfo;     //указатель на данные меша

public:
        // Создает объект с мешем
        Entity(MeshInfo* meshInfo);

        // Возвращает указатель на данные меша
        MeshInfo*       meshInfo() const;
};

#endif // ENTITY_H
