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

void Texture::bind() {
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
