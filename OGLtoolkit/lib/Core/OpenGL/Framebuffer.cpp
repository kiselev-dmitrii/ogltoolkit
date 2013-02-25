#include "Framebuffer.h"
#include "lib/Utils/Debug.h"

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

void Framebuffer::attachAsColorBuffer(const ColorTexture2D *texture, int mipmapLevel, int number) {
        bind();
        glFramebufferTexture2D(m_target, GL_COLOR_ATTACHMENT0+number, GL_TEXTURE_2D, texture->handle(), mipmapLevel);
}

void Framebuffer::attachAsColorBuffer(const TextureCube* texture, CubeSide::Enum side, int mipmapLevel, int number) {
        bind();
        glFramebufferTexture2D(m_target, GL_COLOR_ATTACHMENT0+number, side, texture->handle(), mipmapLevel);
}

void Framebuffer::attachAsColorBuffer(const Renderbuffer* renderbuffer, int number) {
        bind();
        glFramebufferRenderbuffer(m_target, GL_COLOR_ATTACHMENT0+number, GL_RENDERBUFFER, renderbuffer->handle());
}

void Framebuffer::attachAsDepthBuffer(const DepthTexture2D *texture, int mipmapLevel) {
        bind();
        glFramebufferTexture2D(m_target, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->handle(), mipmapLevel);
}

void Framebuffer::attachAsDepthBuffer(const Renderbuffer* renderbuffer) {
        bind();
        glFramebufferRenderbuffer(m_target, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->handle());
}

void Framebuffer::attachAsStencilBuffer(const Texture2D* texture, int mipmapLevel) {
        bind();
        glFramebufferTexture2D(m_target, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture->handle(), mipmapLevel);
}

void Framebuffer::attachAsStencilBuffer(const Renderbuffer* renderbuffer) {
        bind();
        glFramebufferRenderbuffer(m_target, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->handle());
}

bool Framebuffer::isValid() {
        bind();

        GLenum status;
        status = glCheckFramebufferStatus(m_target);
        switch (status) {
                case GL_FRAMEBUFFER_COMPLETE:
                        return true;
                        break;

                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                        DEBUG("Error: framebuffer incomplete attachment");
                        return false;
                        break;

                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                        DEBUG("Error: framebuffer has no attachments");
                        return false;
                        break;

                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                        DEBUG("Error: framebuffer incomplete draw buffer");
                        return false;
                        break;

                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                        DEBUG("Error: framebuffer incomplete read buffer");
                        return false;
                        break;

                case GL_FRAMEBUFFER_UNSUPPORTED:
                        DEBUG("Error: framebuffer unsupported");
                        return false;
                        break;

                default:
                        DEBUG("Error: unknown error");
                        return false;
                        break;
        }
}
