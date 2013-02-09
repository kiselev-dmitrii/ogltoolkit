#include "Texture2D.h"
#include "lib/Debug/Debug.h"

Texture2D::Texture2D(const string &filename) : Texture(TextureTarget::TEXTURE_2D) {
        uploadImage(filename);
}

Texture2D::Texture2D(int width, int height, TextureType::Enum type) : Texture(TextureTarget::TEXTURE_2D) {
        //Количество бит на тип соответствует 32-битной архитектуре.
        GLenum internalFormat;
        if(type == TextureType::BYTE || type == TextureType::UBYTE) internalFormat = GL_RGBA8;
        else if(type == TextureType::INT) internalFormat = GL_RGBA32I;
        else if(type == TextureType::UINT) internalFormat = GL_RGBA32UI;
        else if(type == TextureType::FLOAT) internalFormat = GL_RGBA32F;

        glTexImage2D(m_target, 0, internalFormat, width, height, 0, GL_BGRA, type, NULL);
}

Texture2D::Texture2D() : Texture(TextureTarget::TEXTURE_2D) { }

void Texture2D::uploadImage(const string &filename) {
        Image img(filename);
        uploadImage(img);
}

void Texture2D::uploadImage(const Image &image) {
        TRACE("Пока mipmap не используется, так что все грузится в уровень 0");
        bind();
        glTexImage2D(m_target, 0, image.format(), image.width(), image.height(), 0, image.format(), image.type(), image.data());
}
