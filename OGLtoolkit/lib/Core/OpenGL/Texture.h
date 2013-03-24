#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

/** Точка привязки
  */
namespace TextureTarget {
        enum Enum {
                TEXTURE_2D = GL_TEXTURE_2D,
                CUBEMAP = GL_TEXTURE_CUBE_MAP
        };
}

/** Режим интерполяции текселей
  */
namespace TextureFilter {
        enum Enum {
                NEAREST = GL_NEAREST,
                LINEAR = GL_LINEAR
        };
}

/** Режим наложения (обертки) текстуры на меш
  */
namespace WrapMode {
        enum Enum {
                REPEAT = GL_REPEAT,                     //текстура повторяется
                REPEAT_MIRRORED = GL_MIRRORED_REPEAT,   //текстура повторяется с отражением
                CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,       //граничные пиксели текстуры растягиваются
                CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER    //граница текстуры растягивается
        };
}

/** Тип компонент текселей в текстуре
  */
namespace TextureType {
enum Enum {
        UBYTE = GL_UNSIGNED_BYTE,
        BYTE = GL_BYTE,

        USHORT = GL_UNSIGNED_SHORT,
        SHORT = GL_SHORT,

        INT = GL_INT,
        UINT = GL_UNSIGNED_INT,

        FLOAT = GL_FLOAT
};
}

/** Внутренний формат компонентов в текстуре.
  * Определяет внутреннее представление компоненты текселя в пямяти видеокарты
  */
namespace TextureInternal {
enum Enum {
        DEPTH32F = GL_DEPTH_COMPONENT32F,       //1 float компонента
        DEPTH32 = GL_DEPTH_COMPONENT32,         //32 бит на 1 компоненту
        DEPTH24 = GL_DEPTH_COMPONENT24,         //24 бит на 1 компоненту
        DEPTH16 = GL_DEPTH_COMPONENT16,         //16 бит на 1 компоненту
        DEPTH = GL_DEPTH_COMPONENT,             //выбирается автоматически, в зависимости от других параметров

        RGBA8 = GL_RGBA8,                       //4 byte компоненты
        RGBA32I = GL_RGBA32I,                   //4 integer компоненты
        RGBA32UI = GL_RGBA32UI,                 //4 unsigned int компоненты
        RGBA32F = GL_RGBA32F                    //4 float компоненты
};
}

/** Определяет, как будут трактоваться загружаемые/выгружаемые массивы данных.
  * Это представление отделено от типа.
  * Играет роль только взаимное расположение компонент и их количество
  */
namespace TextureFormat {
enum Enum {
        DEPTH = GL_DEPTH_COMPONENT,     //1 компонента (используется в Depth текстурах)

        RGBA = GL_RGBA,                 //4 комопоненты
        BGRA = GL_BGRA,

        RGB = GL_RGB,                   //3 компоненты
        BGR = GL_BGR,

        RG = GL_RG,                     //2 компоненты

        R = GL_RED                      //1 компонента
};
}

/** Базовый класс OpenGL текстур
  * Не имеет виртуальных функций.
  */
class Texture {
protected:
        GLuint                  m_handle;       //идентификатор
        TextureTarget::Enum     m_target;       //точка связывания

public:
        // Создает текстуру с точкой привязки к target
        Texture(TextureTarget::Enum target);
        virtual ~Texture();

        // Установка интерполяции при уменьшении и увеличении текстуры
        void    setFilterMinimization(TextureFilter::Enum filter);
        void    setFilterMagnification(TextureFilter::Enum filter);

        // Установка режима накладывания текстуры вдоль соответствующей оси, в случае если координаты вышли за [0;1]x[0;1]
        void    setWrapS(WrapMode::Enum mode);
        void    setWrapT(WrapMode::Enum mode);
        void    setWrapR(WrapMode::Enum mode);

        // Возвращает размеры текстуры на mipmap уровне mipmapLevel
        int     width(int mipmapLevel=0) const;
        int     height(int mipmapLevel=0) const;
        int     depth(int mipmapLevel=0) const;

        // Привязывает текстуру к контексту
        void    bind() const;

        // Возвращает идентификатор текстуры
        GLuint  handle() const;

        // Возвращает точку привязки
        GLenum  target() const;
};

#endif // TEXTURE_H
