#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include "Texture.h"
#include "lib/Data/Image.h"

/** Класс двумерной текстуры
  */
class Texture2D : public Texture {
public:
        // Конcтруирует текстуру, с изображением из filename
        Texture2D(const string &filename);
        // Создает пустую RGBA текстуру размера width на height. Каждая компонента представляет из себя ячейку типа type.
        Texture2D(int width, int height, TextureType::Enum type=TextureType::UBYTE);
        // Создает пустую тестуру
        Texture2D();

        // Загружает изображение в текстуру (в видеокарту)
        void    uploadImage(const string &filename);
        void    uploadImage(const Image &image);
};

#endif // TEXTURE2D_H
