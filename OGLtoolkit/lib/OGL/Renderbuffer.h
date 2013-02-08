#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include <GL/glew.h>

namespace RenderbufferFormat {
enum Enum {
        DEPTH_16 = GL_DEPTH_COMPONENT16,        //16 bit
        DEPTH_24 = GL_DEPTH_COMPONENT24,        //24 bit
        DEPTH_32F = GL_DEPTH_COMPONENT32F       //32 bit во float
};
}

/** Класс-обертка для Renderbuffer Object.
  * Служит в качестве render target, т.е. сюда будет происходить рендер.
  * Используется вместо текстуры в Framebuffer, если не пременяется пост-обработка
*/
class Renderbuffer {
private:
        GLuint  m_handle;
public:
        // Конструирует пустой renderbuffer
        Renderbuffer();
        // Конструирует renderbuffer размера width на height,
        // с внутренним форматом пикселей internalFormat
        Renderbuffer(int width, int height, RenderbufferFormat::Enum internalFormat);

        // Уничтожает renderbuffer
        ~Renderbuffer();

        // Привязывает renderbuffer к контексту
        void    bind();

        // Возвращает идентификатор renderbuffer
        GLuint  handle() const;
};

#endif // RENDERBUFFER_H
