#include "Texture.h"

Texture::Texture(TextureTarget::Enum target) {
        m_target = target;
        glGenTextures(1, &m_handle);

        // По-дефолту линейная фильтрация
        setFilterMinimization(TextureFilter::LINEAR);
        setFilterMagnification(TextureFilter::LINEAR);
}

Texture::~Texture() {
        glDeleteTextures(1, &m_handle);
}

void Texture::bind() const {
        glBindTexture(m_target, m_handle);
}

void Texture::setFilterMagnification(TextureFilter::Enum filter) {
        bind();
        glTexParameterf(m_target, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::setFilterMinimization(TextureFilter::Enum filter) {
        bind();
        glTexParameterf(m_target, GL_TEXTURE_MIN_FILTER, filter);
}

void Texture::setWrapS(WrapMode::Enum mode) {
        bind();
        glTexParameterf(m_target, GL_TEXTURE_WRAP_S, mode);
}

void Texture::setWrapT(WrapMode::Enum mode) {
        bind();
        glTexParameterf(m_target, GL_TEXTURE_WRAP_T, mode);
}

void Texture::setWrapR(WrapMode::Enum mode) {
        bind();
        glTexParameterf(m_target, GL_TEXTURE_WRAP_R, mode);
}

GLuint Texture::handle() const {
        return m_handle;
}

GLenum Texture::target() const {
        return m_target;
}

int Texture::width(int mipmapLevel) const {
        int result;
        bind();
        glGetTexLevelParameteriv(m_target, mipmapLevel, GL_TEXTURE_WIDTH, &result);
        return result;
}

int Texture::height(int mipmapLevel) const {
        int result;
        bind();
        glGetTexLevelParameteriv(m_target, mipmapLevel, GL_TEXTURE_HEIGHT, &result);
        return result;
}

int Texture::depth(int mipmapLevel) const {
        int result;
        bind();
        glGetTexLevelParameteriv(m_target, mipmapLevel, GL_TEXTURE_DEPTH, &result);
        return result;
}

