#include "Image.h"
#include "lib/Debug/Debug.h"

bool Image::m_isDevilInit = false;

void Image::initDevil() {
        if (m_isDevilInit) return;

        // Проверяем версию библиотек
        if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
                DEBUG("Incorect version of DEVil library");
                return;
        }

        // Инициализируем
        ilInit();
        iluInit();

        m_isDevilInit = true;
}

void Image::load(const string &filename) {
        ilBindImage(m_id);

        if (!ilLoadImage(filename.c_str())) {
                DEBUG("Cannot load image from file " << filename);
                return;
        }
}

Image::Image(const string &filename) {
        initDevil();

        ilGenImages(1, &m_id);
        load(filename);
}

Image::~Image() {
        ilDeleteImages(1, &m_id);
}

int Image::width() const {
        ilBindImage(m_id);
        return ilGetInteger(IL_IMAGE_WIDTH);
}

int Image::height() const {
        ilBindImage(m_id);
        return ilGetInteger(IL_IMAGE_HEIGHT);
}
int Image::bytePerPixel() const {
        ilBindImage(m_id);
        return ilGetInteger(IL_IMAGE_BPP);
}

int Image::format() const {
        ilBindImage(m_id);
        return ilGetInteger(IL_IMAGE_FORMAT);
}

int Image::type() const {
        ilBindImage(m_id);
        return ilGetInteger(IL_IMAGE_TYPE);
}

void *Image::data() const {
        ilBindImage(m_id);
        return ilGetData();
}

