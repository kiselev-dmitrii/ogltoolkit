#ifndef TEXTUREUNIT_H
#define TEXTUREUNIT_H

#include <GL/glew.h>
#include <vector>

using std::vector;
class Texture;

/** Класс-обертка для TextureImageUnit
  */
class TextureUnit {
private:
        static int              m_countUsed;    //кол-во занятых TIU
        static vector<bool>     m_usedUnits;    //если true, то i-тый unit занят

        int                     m_number;       //номер текстурного юнита

private:
        // Ищет свободный блок в векторе и возвращает его номер.
        // Делает его занятым
        static int              assignUnit();
        // Освобождает unit с номером i
        static void             freeUnit(int i);

        // Делает данный TUI активным
        void                    bind();

public:
        // Конструктор и деструктор TIU
        TextureUnit();
        ~TextureUnit();

        // Связывает/овязывает текстуру с данным TIU
        void    bindTexture(const Texture &texture);
        void    unbindTexture(const Texture &texture);

        // Возвращает номер данного TIU
        int     number() const;
};

#endif // TEXTUREUNIT_H
