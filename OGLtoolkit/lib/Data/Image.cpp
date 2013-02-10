#include "Image.h"
#include "lib/Debug/Debug.h"
#include "lib/OGL/Texture2D.h"

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

void Image::load(const Texture2D &texture, int level) {
        int width = texture.width();
        int height = texture.height();

        unsigned char pixels[3*width*height];                                   //временное место для изображения в памяти
        texture.bind();
        glGetTexImage(GL_TEXTURE_2D, level, GL_RGB, GL_UNSIGNED_BYTE, pixels);  //копируем в pixels

        ilBindImage(m_id);
        ilTexImage(width,height,1, 3, IL_RGB, IL_UNSIGNED_BYTE, pixels);        //из pixels инициализируем картунку
}

void Image::save(const string &filename, bool overwrite) {
        ilBindImage(m_id);

        if (overwrite) ilEnable(IL_FILE_OVERWRITE);

        //Сохраняем
        if (!ilSaveImage(filename.c_str())) {
                DEBUG("Cannot save image to file " << filename);
                return;
        }

        ilDisable(IL_FILE_OVERWRITE);
}

Image::Image(const string &filename) {
        initDevil();

        ilGenImages(1, &m_id);
        load(filename);
}

Image::Image(const Texture2D &texture, int level) {
        initDevil();

        ilGenImages(1, &m_id);
        load(texture, level);
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

