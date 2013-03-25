#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"
#include "../Data/Image.h"

using namespace glm;

/** Класс двумерной текстуры.
  * Представляет к использованию общие методы, для всех двумерных текстур
  * Обычно, клиентом не должен использовать конструктор Texture2D, т.к. он слишком универсален
  */
class Texture2D : public Texture {
public:
        // Создает пустую текстуру с заданным размером, форматом, внутренним форматом
        Texture2D(int width, int height, TextureInternal::Enum internalFormat, TextureFormat::Enum format, TextureType::Enum type);
        // Создают текстуру, но место в видеопамяти еще не выделяется
        Texture2D();
};

/** Класс цветной двумерной текстуры
  */
class ColorTexture2D : public Texture2D {
public:
        // Создает текстуру с изображением из filename.
        ColorTexture2D(const string &filename, bool generateMipmaps=true);
        // Создает пустую RGBA текстуру размера size. Компоненты текселей получают тип type
        ColorTexture2D(const ivec2& size, TextureType::Enum type=TextureType::UBYTE);

        // Загружает изображение в текстуру
        void    uploadImage(const string &filename, bool generateMipmaps=true);
        void    uploadImage(const Image &image, bool generateMipmaps=true);
};

/** Класс двумерной текстуры глубины
  */
class DepthTexture2D : public Texture2D {
public:
        // Создает пустую текстуру глубины с размером size и указанным типом компонент
        DepthTexture2D(const ivec2& size, TextureType::Enum type=TextureType::UINT);
};

#endif // TEXTURE2D_H
