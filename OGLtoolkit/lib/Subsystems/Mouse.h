#ifndef MOUSE_H
#define MOUSE_H

#include <glm/glm.hpp>
using glm::ivec2;
using namespace glm;

/** Статический класс для управления курсором мыши
  */
class Mouse {
public:
        // Установка/получение позиции
        static void     setPos(const ivec2 &pos);
        static void     setPos(int x, int y);
        static ivec2    pos();

        // Показать/скрыть мышь
        static void     hide();
        static void     show();
};

#endif // MOUSE_H
