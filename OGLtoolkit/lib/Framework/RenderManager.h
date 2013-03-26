#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <map>
#include <string>
#include "UniformSupplier.h"
#include "EntityManager.h"
#include "AbstractCamera.h"

using namespace std;

class GpuProgram;
class Entity;

/** Перечисление, задающее грани полигона
  */
namespace PolygonFace {
enum Enum {
        FRONT = GL_FRONT,
        BACK = GL_BACK,
        FRONT_AND_BACK = GL_FRONT_AND_BACK,
        NONE = GL_NONE
};
}

typedef map<string, GpuProgram*>        MapGpuProgram;

/** В обязанности данного класса входит:
  *     - Отрисовка объектов класса Entity в соответствии с текущей GPU программой.
  *     - Передача в GPU программу матриц, причем только тех, которые нужны программе.
  * Планируется передавать Entity ассоциативным массивом (ссылку на который будет возвращать EntityManager).
  */
class RenderManager {
private:
        MapGpuProgram   m_programs;

        GpuProgram*     m_currentProgram;
        AbstractCamera* m_currentCamera;

        UniformSupplier m_uniformSupplier;      //занимается определением, что нужно шейдеру

        bool            m_isCullFaceEnabled;    //определяет, включено ли отсечение граней

private:
        // Обновляет значения некоторых uniform переменных
        void    uploadUniforms(Entity* entity);

private:
        // Закрытый конструктор
        RenderManager();
        RenderManager(const RenderManager&);
        RenderManager& operator=(const RenderManager&);

public:
        // Точка доступа к объекту
        static RenderManager* instance();
        // Деструктор
        ~RenderManager();

        // Добавляет GPU программу в список доступных
        void            addProgram(const string& programName, GpuProgram *program);
        // Удаляет GPU программу из списка доступных
        void            removeProgram(const string& programName);
        void            removeAllProgram();
        // Возвращает GPU программу по имени
        GpuProgram*     program(const string& programName);

        // Устанавливает/возвращает текущую активную GPU программу
        void            setCurrentProgram(const string& programName);
        GpuProgram*     currentProgram();

        // Устанавливает/возращает текущую камеру
        void            setCurrentCamera(AbstractCamera* camera);
        AbstractCamera* currentCamera();

        // Отрисовывает объекты типа Enity
        void            render(MapEntity *entities);
        void            render(Entity* entity);

        // Отсекает задние или передние грани полигонов
        void            setCullFace(PolygonFace::Enum face);

        // Очищает цветовой буфер и буфер глубины
        void            clearColorDepthBuffers();
};

#endif // RENDER_H
