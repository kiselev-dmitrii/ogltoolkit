#ifndef RENDER_H
#define RENDER_H

#include <string>

using namespace std;

class AbstractCamera;
class GpuProgram;
class MapEntity;
class Entity;

/** Класс инкапсулирует настройки, применяемые в процессе дебага приложения.
  * Позволяет отобразить координтные оси, описывающие боксы и т.д
  *
  */
class RenderDebugSettings {
public:
        // Определяет, отрисовывать ли координтные оси у нодов, к которым подключены Entity
        void    showCoordinateAxes(bool isShow=true);
        bool    isShowCoordinateAxes() const;
        // Определяет, отрисовывать bound box
        void    showBoundBox(bool isShow=true);
        bool    isShowBoundBox() const;
        // Определяет, отрисовывать bound sphere
        void    showBoundSphere(bool isShow=true);
        bool    isShowBoundSphere() const;
};

/** В обязанности данного класса входит:
  *     - Отрисовка объектов класса Entity в соответствии с текущей GPU программой.
  *     - Передача в GPU программу матриц, причем только тех, которые нужны программе.
  * Планируется передавать Entity ассоциативным массивом (ссылку на который будет возвращать EntityManager).
  */
class RenderManager {
private:
        // Закрытый конструктор
        RenderManager()        {}

public:
        // Точка доступа к объекту
        static RenderManager*   instance();

        // Добавляет GPU программу в список доступных
        void            addGpuProgram(const GpuProgram& program, const string& name);
        // Удаляет GPU программу из списка доступных
        void            removeGpuProgram(const string& name);
        // Возвращает GPU программу по имени
        GpuProgram*     gpuProgram(const string& name) const;
        // Устанавливает/возвращает текущую активную GPU программу
        void            setCurrentGpuProgram(const string& name);
        GpuProgram*     currentGpuProgram() const;

        // Устанавливает/возращает текущую камеру
        void            setCurrentCamera(AbstractCamera* camera);
        AbstractCamera* currentCamera() const;

        // Отрисовывает объекты типа Enity
        void            render(MapEntity* entities);
        void            render(Entity* entity);

        // Возвращает указатель к настройками отрисовки
        RenderDebugSettings*     debugSettings() const;
};

#endif // RENDER_H
