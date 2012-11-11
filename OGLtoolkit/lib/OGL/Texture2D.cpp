#include "Texture2D.h"
#include "lib/Debug/Debug.h"

Texture2D::Texture2D(const string &filename) : Texture(TextureTarget::TEXTURE_2D) {
        uploadImage(filename);
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
