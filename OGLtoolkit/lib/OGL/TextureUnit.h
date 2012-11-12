#ifndef TEXTUREUNIT_H
#define TEXTUREUNIT_H

#include <GL/glew.h>

/** Класс-обертка для TextureImageUnit
  */
class TextureUnit {
private:
        static int      m_counter;      //счетчик, для определения последнего свободного
        int             m_number;       //номер текстурного юнита

public:
        // Конструктор и деструктор TIU
        TextureUnit();
        ~TextureUnit();

        // Делает данный TUI активным
        void    bind();

        // Возвращает номер данного TIU
        int     number();
};

#endif // TEXTUREUNIT_H
