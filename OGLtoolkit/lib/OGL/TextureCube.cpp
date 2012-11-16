#include "TextureCube.h"
#include "lib/Debug/Debug.h"

void TextureCube::initWrap() {
        setWrapS(WrapMode::CLAMP_TO_EDGE);
        setWrapT(WrapMode::CLAMP_TO_EDGE);
        setWrapR(WrapMode::CLAMP_TO_EDGE);
}

TextureCube::TextureCube() : Texture(TextureTarget::CUBEMAP) {
        initWrap();
}

TextureCube::TextureCube(const string &posX, const string &posY, const string &posZ, const string &negX, const string &negY, const string &negZ) : Texture(TextureTarget::CUBEMAP) {
        uploadImage(CubeSide::POSITIVE_X, posX);
        uploadImage(CubeSide::POSITIVE_Y, posY);
        uploadImage(CubeSide::POSITIVE_Z, posZ);

        uploadImage(CubeSide::NEGATIVE_X, negX);
        uploadImage(CubeSide::NEGATIVE_Y, negY);
        uploadImage(CubeSide::NEGATIVE_Z, negZ);

        initWrap();
}

TextureCube::TextureCube(string path, const string &fileExtension) : Texture(TextureTarget::CUBEMAP) {
        if(path[path.size()-1]=='/') path.erase(path.size()-1, 1);

        uploadImage(CubeSide::POSITIVE_X, path + "/posx." + fileExtension);
        uploadImage(CubeSide::POSITIVE_Y, path + "/posy." + fileExtension);
        uploadImage(CubeSide::POSITIVE_Z, path + "/posz." + fileExtension);

        uploadImage(CubeSide::NEGATIVE_X, path + "/negx." + fileExtension);
        uploadImage(CubeSide::NEGATIVE_Y, path + "/negy." + fileExtension);
        uploadImage(CubeSide::NEGATIVE_Z, path + "/negz." + fileExtension);

        initWrap();
}

void TextureCube::uploadImage(CubeSide::Enum side, const string &filename) {
        Image img(filename);
        uploadImage(side, img);
}

void TextureCube::uploadImage(CubeSide::Enum side, const Image &image) {
        TRACE("Пока mipmap не используется, так что все грузится в уровень 0");
        bind();
        glTexImage2D(side, 0, image.format(), image.width(), image.height(), 0, image.format(), image.type(), image.data());
}
