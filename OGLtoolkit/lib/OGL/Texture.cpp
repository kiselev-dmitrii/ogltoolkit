#include "Texture.h"

Texture::Texture(TextureTarget::Enum target) {
        m_target = target;
        glGenTextures(1, &m_handle);
}

Texture::~Texture() {
        glDeleteTextures(1, &m_handle);
}

void Texture::bind() {
        glBindTexture(m_target, m_handle);
}

void Texture::setAssociatedTextureUnit(size_t textureUnit) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        bind();
}

void Texture::setFilterMagnification(TextureFilter::Enum filter) {
        bind();
        glTexParameterf(m_target, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::setFilterMinimization(TextureFilter::Enum filter) {
        bind();
        glTexParameterf(m_target, GL_TEXTURE_MIN_FILTER, filter);
}