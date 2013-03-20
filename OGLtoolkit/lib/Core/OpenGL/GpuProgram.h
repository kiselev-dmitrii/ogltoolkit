#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

using namespace std;
using namespace glm;

typedef vector<string>  StringList;

/** Типы шейдеров
  */
namespace ShaderType {
enum Enum {
        VERTEX_SHADER = GL_VERTEX_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
        GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
        TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
        TESS_EVAL_SHADER = GL_TESS_EVALUATION_SHADER
};
}

/** Класс, инкапсулирующий объекты ShaderObject и ProgramObject
  */
class GpuProgram {
private:
         GLuint          m_programHandle;

        GLuint          m_vertexHandle;
        GLuint          m_fragmentHandle;
        GLuint          m_geometryHandle;
        GLuint          m_tessControlHandle;
        GLuint          m_tessEvalHandle;

        string          m_log;
        bool            m_isLinked;

        StringList      m_defines;              //макроопределения

private:
        void    init();

        // Создает пустую программу
        bool    createProgram();
        // Загружает в строку *buffer данные из filename
        bool    loadBufferFromFile(const string &filename, string *buffer);
        // Добавляет в начало строки *buffer макроопределения из defines
        void    addDefines(const StringList& defines, string *buffer);
        // Создает шейдер, компилирует его и присоединяет к основной программе
        bool    compileShaderFromString(const string &sourceCode, ShaderType::Enum type);

public:
        // Создает пустой объект
        GpuProgram();
        // Создает программу с загруженными шейдерами (компилирует, линкует)
        GpuProgram(const string &vertexShader, const string &fragmentShader, const StringList& defines = StringList());
        // Аналогично, но принимает на вход путь без расширений (добавляет .vert и .frag)
        GpuProgram(const string &shaders, const StringList& defines = StringList());
        // Разрушает объект
        ~GpuProgram();

        // Устанавливает/возвращает дефайны, которые будут добавлены в каждый шейдер
        void            setDefines(const StringList& defines);
        StringList      defines();

        // Компиляция, линковка
        bool            compileShaderFromFile(const string &filename, ShaderType::Enum type);
        bool            link();
        bool            isLinked();

        // Загружает, компилирует и линкует программу
        // Шейдеры находятся в одном файле, и каждый начинается с комментария "//--Тип_шейдера"
        bool            loadProgram(const string &filename);

        // Делает шейдер текущим или отключает его
        void            bind();
        void            unbind();

        // Установка переменных
        void            setUniform(const string &name, float value);
        void            setUniform(const string &name, int value);
        void            setUniform(const string &name, const vec2 &value);
        void            setUniform(const string &name, const vec3 &value);
        void            setUniform(const string &name, const vec4 &value);
        void            setUniform(const string &name, const mat3 &value);
        void            setUniform(const string &name, const mat4 &value);

        // Устанавливает подряд идущие uniform-subroutine переменные из uniformNames в значения funcNames в шейдере type
        // В uniformNames должны быть указаны все uniform-subroutine переменные или хотябы первые подряд
        void            setSubroutines(ShaderType::Enum type, const StringList &uniformNames, const StringList &funcNames);

        // Устанавливает uniform-subroutine нулевую по порядку
        // Удобно, если в шейдере лишь одна такая переменная
        void            setSubroutine(ShaderType::Enum type, const string &funcName);

        // Возвращает список доступных uniform переменных
        StringList      activeUniforms() const;
        // Возвращает список доступных аттрибутов
        StringList      activeAttributes() const;
        // Возвращает лог
        string          log() const;

        // Возвращает handle программы
        GLuint  handle() const;

};

#endif // SHADER_H
