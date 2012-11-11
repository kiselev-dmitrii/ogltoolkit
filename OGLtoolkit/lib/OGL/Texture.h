#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

namespace TextureTarget {
        enum Enum {
                TEXTURE_2D = GL_TEXTURE_2D,
                CUBEMAP = GL_TEXTURE_CUBE_MAP
        };
}

namespace TextureFilter {
        enum Enum {
                NEAREST = GL_NEAREST,
                LINEAR = GL_LINEAR
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
        void    bind();

        // Устанавливает текстуру в i-тый текстурный блок
        void    setAssociatedTextureUnit(size_t textureUnit);

        // Установка интерполяции при уменьшении и увеличении текстуры
        void    setFilterMinimization(TextureFilter::Enum filter);
        void    setFilterMagnification(TextureFilter::Enum filter);
};

#endif // TEXTURE_H
