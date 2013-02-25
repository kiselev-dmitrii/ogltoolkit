#include "Texture2D.h"
#include "lib/Utils/Debug.h"

Texture2D::Texture2D() : Texture(TextureTarget::TEXTURE_2D) { }

Texture2D::Texture2D(int width, int height, TextureInternal::Enum internalFormat, TextureFormat::Enum format, TextureType::Enum type) : Texture(TextureTarget::TEXTURE_2D) {
        glTexImage2D(m_target, 0, internalFormat, width, height, 0, format, type, NULL);
}

//==================================================================================================================//

ColorTexture2D::ColorTexture2D(const string &filename, bool generateMipmaps) : Texture2D() {
        uploadImage(filename, generateMipmaps);

        setFilterMinimization(TextureFilter::LINEAR);
        setFilterMagnification(TextureFilter::LINEAR);
}

ColorTexture2D::ColorTexture2D(int width, int height, TextureType::Enum type) : Texture2D() {
        //Количество бит на тип соответствует 32-битной архитектуре.
        TextureInternal::Enum internalFormat;
        if(type == TextureType::BYTE || type == TextureType::UBYTE) internalFormat = TextureInternal::RGBA8;
        else if(type == TextureType::INT) internalFormat = TextureInternal::RGBA32I;
        else if(type == TextureType::UINT) internalFormat = TextureInternal::RGBA32UI;
        else if(type == TextureType::FLOAT) internalFormat = TextureInternal::RGBA32F;

        glTexImage2D(m_target, 0, internalFormat, width, height, 0, TextureFormat::BGRA, type, NULL);

        setFilterMinimization(TextureFilter::NEAREST);
        setFilterMagnification(TextureFilter::NEAREST);
}

void ColorTexture2D::uploadImage(const string &filename, bool generateMipmaps) {
        Image img(filename);
        uploadImage(img, generateMipmaps);
}

void ColorTexture2D::uploadImage(const Image &image, bool generateMipmaps) {
        bind();
        glTexImage2D(m_target, 0, image.format(), image.width(), image.height(), 0, image.format(), image.type(), image.data());
        if(generateMipmaps) glGenerateMipmap(m_target);
}

//==================================================================================================================//

DepthTexture2D::DepthTexture2D(int width, int height, TextureType::Enum type) : Texture2D() {
        glTexImage2D(m_target, 0, TextureInternal::DEPTH, width, height, 0, TextureFormat::DEPTH, type, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        setFilterMinimization(TextureFilter::NEAREST);
        setFilterMinimization(TextureFilter::NEAREST);
}
