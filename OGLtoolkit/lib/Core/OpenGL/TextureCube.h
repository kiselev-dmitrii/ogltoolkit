#ifndef TEXTURECUBE_H
#define TEXTURECUBE_H

#include "Texture.h"
#include "../Data/Image.h"

namespace CubeSide {
        enum Enum {
                POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,

                NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };
}

/** Класс кубической текстуры
  */
class TextureCube : public Texture {
private:
        // Устанавливает начальный режим наложения текстуры
        void    initWrap();
public:
        // Создает кубическую текстуру.
        // pos - положительное направление некоторой оси
        // neg - отрицаьельно направление
        TextureCube(const string &posX, const string &posY, const string &posZ,
                    const string &negX, const string &negY, const string &negZ);

        // Создает кубическую текстуру из изображений path/[posx|...|negz].fileExtension
        TextureCube(string path, const string &fileExtension);

        // Создает пустую кубическую RGBA текстуру размера size.
        // Каждая компонента представляет из себя ячейку типа type.
        TextureCube(int size, TextureType::Enum type=TextureType::UBYTE);

        // Создает пустую кубическую текстуру
        TextureCube();

        // Загружает изображение в качестве сторны side куба
        void    uploadImage(CubeSide::Enum side, const string &filename);
        void    uploadImage(CubeSide::Enum side, const Image &image);
};

#endif // TEXTURECUBE_H
