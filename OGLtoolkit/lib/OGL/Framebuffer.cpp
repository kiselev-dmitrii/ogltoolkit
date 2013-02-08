#include "Framebuffer.h"

Framebuffer::Framebuffer(FramebufferTarget::Enum target) {
        glGenFramebuffers(1, &m_handle);
        m_target = target;
}

Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &m_handle);
}

void Framebuffer::bind() {
        glBindFramebuffer(m_target, m_handle);
}

void Framebuffer::unbind() {
        glBindFramebuffer(m_target, 0);
}

void Framebuffer::attachAsColorBuffer(const Texture2D &texture, int mipmapLevel, int number) {
        bind();
        glFramebufferTexture2D(m_target, GL_COLOR_ATTACHMENT0+number, GL_TEXTURE_2D, texture.handle(), mipmapLevel);
}

void Framebuffer::attachAsColorBuffer(const Renderbuffer &renderbuffer, int number) {
        bind();
        glFramebufferRenderbuffer(m_target, GL_COLOR_ATTACHMENT0+number, GL_RENDERBUFFER, renderbuffer.handle());
}

void Framebuffer::attachAsDepthBuffer(const Texture2D &texture, int mipmapLevel) {
        bind();
        glFramebufferTexture2D(m_target, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.handle(), mipmapLevel);
}

void Framebuffer::attachAsDepthBuffer(const Renderbuffer &renderbuffer) {
        bind();
        glFramebufferRenderbuffer(m_target, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.handle());
}

void Framebuffer::attachAsStencilBuffer(const Texture2D &texture, int mipmapLevel) {
        bind();
        glFramebufferTexture2D(m_target, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.handle(), mipmapLevel);
}

void Framebuffer::attachAsStencilBuffer(const Renderbuffer &renderbuffer) {
        bind();
        glFramebufferRenderbuffer(m_target, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.handle());
}
