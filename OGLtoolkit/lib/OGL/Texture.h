#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

/** Точка привязки
  */
namespace TextureTarget {
        enum Enum {
                TEXTURE_2D = GL_TEXTURE_2D,
                CUBEMAP = GL_TEXTURE_CUBE_MAP
        };
}

/** Режим интерполяции текселей
  */
namespace TextureFilter {
        enum Enum {
                NEAREST = GL_NEAREST,
                LINEAR = GL_LINEAR
        };
}

/** Режим наложения (обертки) текстуры на меш
  */
namespace WrapMode {
        enum Enum {
                REPEAT = GL_REPEAT,                     //текстура повторяется
                REPEAT_MIRRORED = GL_MIRRORED_REPEAT,   //текстура повторяется с отражением
                CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,       //граничные пиксели текстуры растягиваются
                CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER    //граница текстуры растягивается
        };
}

/** Тип компонент пикселей в текстуре
  */
namespace TextureType {
enum Enum {
        UBYTE = GL_UNSIGNED_BYTE,
        BYTE = GL_BYTE,
        INT = GL_INT,
        UINT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT
};
}


/** Базовый класс OpenGL текстур
  * Не имеет виртуальных функций.
  */
class Texture {
protected:
        GLuint                  m_handle;       //идентификатор
        TextureTarget::Enum     m_target;       //точка связывания

public:
        // Создает текстуру с точкой привязки к target
        Texture(TextureTarget::Enum target);
        ~Texture();

        // Биндит текстуру
        void    bind() const;

        // Установка интерполяции при уменьшении и увеличении текстуры
        void    setFilterMinimization(TextureFilter::Enum filter);
        void    setFilterMagnification(TextureFilter::Enum filter);

        // Установка режима накладывания текстуры вдоль соответствующей оси, в случае если координаты вышли за [0;1]x[0;1]
        void    setWrapS(WrapMode::Enum mode);
        void    setWrapT(WrapMode::Enum mode);
        void    setWrapR(WrapMode::Enum mode);

        // Возвращает идентификатор текстуры
        GLuint  handle() const;

        // Возвращает размеры текстуры на mipmap уровне mipmapLevel
        int     width(int mipmapLevel=0) const;
        int     height(int mipmapLevel=0) const;
        int     depth(int mipmapLevel=0) const;
};

#endif // TEXTURE_H
