#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
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

/** Синглтон основного приложения.
  * Содержит основной цикл приложения.
  * Для создание окна используется GLFW
  */
class Application {
private:
        Window          m_window;               //главное окно приложения
        AbstractScene*  m_scene;

private:
        // Инициализирование подсистем и т.д
        bool            init();
        // Главный цикл
        void            loop();
        // Завершение
        void            terminate();

private:
        // Статические функции, которые вызывает GLFW
        static void     onResizeScene(int width, int height);
        static void     onMouseMove(int x, int y);
        static void     onKey(int key, int action);

private:
        // Закрытый конструктор и деструктор
        Application();
        ~Application();

public:
        // Получение сущности
        static Application* instance();

        // Возвращает указатель на окно. Используется для настройки окна перед запуском
        Window*         window();

        // Установка сцены в которой происходит прорисовка
        void            setScene(AbstractScene *scene);
        AbstractScene*  scene();

        // Точка входа в основной цикл приложения
        // Возвращает код завершения приложения
        int             exec();
};

#endif // APPLICATION_H
