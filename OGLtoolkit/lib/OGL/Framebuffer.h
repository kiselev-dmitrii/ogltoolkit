#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include "Texture2D.h"
#include "Renderbuffer.h"

namespace FramebufferTarget {
enum Enum {
        READ_ONLY = GL_READ_FRAMEBUFFER,
        WRITE_ONLY = GL_DRAW_FRAMEBUFFER,
        READ_WRITE = GL_FRAMEBUFFER
};
}

/** Класс-обертка для Framebuffer Object. Служит для рендеринга в текстуру или в рендер буфер
  */
class Framebuffer {
private:
        GLuint                  m_handle;
        FramebufferTarget::Enum m_target;

public:
        // Создает FBO
        Framebuffer(FramebufferTarget::Enum target=FramebufferTarget::READ_WRITE);
        // Удаляет FBO
        ~Framebuffer();

        // Привязывает/отвязывает FBO
        void bind();
        void unbind();

        // Присоединяет к FBO текстуру в качестве цветового буфера c номером number
        void attachAsColorBuffer(const Texture2D& texture, int mipmapLevel=0, int number=0);
        void attachAsColorBuffer(const Renderbuffer& renderbuffer, int number=0);

        // Присоединяет к FBO текстуру/рендербуфер в качестве буфера глубины
        void attachAsDepthBuffer(const Texture2D& texture, int mipmapLevel=0);
        void attachAsDepthBuffer(const Renderbuffer& renderbuffer);

        // Присоединяет к FBO текстуру в качестве буфера трафарета
        void attachAsStencilBuffer(const Texture2D& texture, int mipmapLevel=0);
        void attachAsStencilBuffer(const Renderbuffer& renderbuffer);
};

#endif // FRAMEBUFFER_H
