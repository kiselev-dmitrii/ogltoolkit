#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

/** Класс, представляющий интерфейс ко всем сценам
    Данный класс будет наследоватся конкретной реализацией.
    Далее, используя какую-нибудь библиотеку или тулкит (например QGLWidget),
    методы данного класса будут вызываться в вызовах на инициализацию, изменение размеров окна, апдейт и прорисовку
  */
class AbstractScene {
public:
        virtual ~AbstractScene() {}

        // Выполняется загрузка ресурсов, инициализация шейдеров и т.д
        virtual void    init() = 0;
        // Вызывается при изменении размеров окна
        virtual void    resize(int w, int h) = 0;
        // Служит для обновления анимации спустя время t
        virtual void    update(float deltaTime) = 0;
        // Отрисовывает сцену
        virtual void    render() = 0;
};

#endif // ABSTRACTSCENE_H
