#ifndef IMAGE_H
#define IMAGE_H

#include <IL/il.h>
#include <IL/ilu.h>
#include <string>

using namespace std;
class Texture2D;

/** Класс, хранящий данные изображения
  * А также информацию о нем
  */
class Image {
private:
        ILuint          m_id;
        static bool     m_isDevilInit;

private:
        // Выполняет процедуру инициализации библиотеки DEVIL
        void    initDevil();

public:
        // Создает изображение из файла
        Image(const string &filename);
        // Создает изображение из текстуры
        Image(const Texture2D &texture, int level=0);

        // Дестурктор. Изображение уничтожается
        ~Image();

        // Загружает изображение с файла или текстуры
        void    load(const string &filename);
        void    load(const Texture2D &texture, int level=0);

        // Сохраняет изображение в файл
        void    save(const string &filename, bool overwrite=false);

        // Возвращает ширину
        int     width() const;
        // Возвращает высоту
        int     height() const;
        // Возвращает кол-во байт на пиксель
        int     bytePerPixel() const;
        // Возвращает формат изображения (RGB, RGBA, BGR и т.д)
        int     format() const;
        // Возвращает тип, используемый для представления компонент пикселя
        int     type() const;

        // Возвращает указатель на начало данных
        void*   data() const;
};

#endif // IMAGE_H
