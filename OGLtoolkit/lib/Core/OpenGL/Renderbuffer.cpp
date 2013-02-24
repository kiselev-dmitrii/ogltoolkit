#include "Renderbuffer.h"

Renderbuffer::Renderbuffer() {
        glGenRenderbuffers(1, &m_handle);
}

Renderbuffer::Renderbuffer(int width, int height, RenderbufferFormat::Enum internalFormat) {
        glGenRenderbuffers(1, &m_handle);
        glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
        glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
}

Renderbuffer::~Renderbuffer() {
        glDeleteRenderbuffers(1, &m_handle);
}

void Renderbuffer::bind() {
        glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
}

GLuint Renderbuffer::handle() const {
        return m_handle;
}
