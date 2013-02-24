#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <memory>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include "lib/OGL/AbstractScene.h"
using glm::ivec2;
using std::string;
using namespace glm;
using namespace std;

/** Структура для хранения информации о OpenGL контексте окна
  */
struct Context {
        int     samples;
        int     majorVersion;
        int     minorVersion;
        int     profile;
};

/** Класс окна приложения.
  */
class Window {
private:
        Context m_context;
        ivec2   m_size;
        ivec2   m_pos;
        string  m_title;
        bool    m_isFullscreen;
        bool    m_isOpened;             //открыто ли окно?
public:
        Window();
        ~Window();

        // Открывает окно. GLFW должен быть проинициализирован
        bool    openWindow();

        // Устанавливает заголовок окна
        void    setTitle(const string &title);
        string  title();

        // Устанавливает размеры окна
        void    setSize(const ivec2 &size);
        ivec2   size();

        // Устанавливает позицию окна
        void    setPos(const ivec2 &pos);
        ivec2   pos();

        // Устанавливает полноэкранный режим окна
        void    setFullscreen(bool value);
        bool    fullscreen();

        // Возвращает координаты центра окна
        ivec2   center();
};

/** Статический класс основного приложения.
  * Содержит основной цикл приложения.
  * Для создание окна используется GLFW
  */
class Application {
private:
        static Window                   m_window;               //главное окно приложения
        static auto_ptr<AbstractScene>  m_scene;                //auto_ptr для того, чтобы объект по указателю разрушался

private:
        // Инициализирование подсистем и т.д
        static bool             init();
        // Главный цикл
        static void             loop();
        // Завершение
        static void             terminate();

private:
        //Вызывается при изменении размеров окна
        static void             onResizeScene(int width, int height);

        //Статический класс лучше не создавать
        Application();

public:
        // Возвращает указатель на окно. Используется для настройки окна перед запуском
        static Window*          window();

        // Установка сцены в которой происходит прорисовка
        static void             setScene(AbstractScene *scene);
        static AbstractScene*   scene();

        // Точка входа в основной цикл приложения
        // Возвращает код завершения приложения
        static int              exec();
};

#endif // APPLICATION_H
