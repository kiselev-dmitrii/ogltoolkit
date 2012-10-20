#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

using std::string;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

using namespace std;
using namespace glm;

/** Типы шейдеров
  */
namespace ShaderType {
enum Enum {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        GEOMETRY_SHADER,
        TESS_CONTROL_SHADER,
        TESS_EVAL_SHADER
};
}

/** Класс, инкапсулирующий объекты ShaderObject и ProgramObject
  */
class GpuProgram {
private:
        GLuint  m_programHandle;

        GLuint  m_vertexHandle;
        GLuint  m_fragmentHandle;
        GLuint  m_geometryHandle;
        GLuint  m_tessControlHandle;
        GLuint  m_tessEvalHandle;

        string  m_log;
        bool    m_isLinked;

private:
        bool    createProgram();
        bool    loadBufferFromFile(const string &filename, string *buffer);
        bool    compileShaderFromString(const string &sourceCode, ShaderType::Enum type);

public:
        // Конструктор, деструктор
        GpuProgram();
        ~GpuProgram();

        // Компиляция, линковка
        bool    compileShaderFromFile(const string &filename, ShaderType::Enum type);
        bool    link();
        bool    isLinked();

        // Загружает, компилирует и линкует программу
        // Шейдеры находятся в одном файле, и каждый начинается с комментария "//--Тип_шейдера"
        bool    loadProgram(const string &filename);

        // Делает шейдер текущим или отключает его
        void    bind();
        void    unbind();

        // Установка переменных
        void    setUniform(const string &name, float value);
        void    setUniform(const string &name, int value);
        void    setUniform(const string &name, const vec3 &value);
        void    setUniform(const string &name, const vec4 &value);
        void    setUniform(const string &name, const mat3 &value);
        void    setUniform(const string &name, const mat4 &value);

        // Возвращает handle программы
        GLuint  handle() const;

        // Дебаг
        string  getLog();
        void    showLog();
        void    showActiveUniforms();
        void    showActiveAttributes();

};

#endif // SHADER_H
