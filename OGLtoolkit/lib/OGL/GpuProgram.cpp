#include <fstream>
#include <string>
#include <iostream>
#include "GpuProgram.h"
#include "lib/Debug/Debug.h"

GpuProgram::GpuProgram() {
        m_programHandle = 0;
        m_vertexHandle = 0;
        m_fragmentHandle = 0;
        m_geometryHandle = 0;
        m_tessControlHandle = 0;
        m_tessEvalHandle = 0;
        m_isLinked = false;
}

GpuProgram::~GpuProgram() {
        if(m_programHandle) glDeleteProgram(m_programHandle);
        glDeleteShader(m_vertexHandle);
        glDeleteShader(m_fragmentHandle);
        glDeleteShader(m_geometryHandle);
        glDeleteShader(m_tessControlHandle);
        glDeleteShader(m_tessEvalHandle);
}

bool GpuProgram::createProgram() {
        // Создаем программу, если не создана
        if(m_programHandle == 0) {
                m_programHandle = glCreateProgram();
                if(m_programHandle == 0) {
                        DEBUG("Cannot create program object");
                        m_log += "Cannot create program object\n";
                        return false;
                }
        }
        return true;
}

bool GpuProgram::loadBufferFromFile(const string &filename, string *buffer) {
        // Получаем код из файла
        ifstream inFile(filename.c_str());
        if(!inFile) {
                DEBUG("Cannot open file");
                m_log += "Cannot open file\n";
                return false;
        }

        char ch;
        while(inFile.get(ch)) *buffer += ch;
        inFile.close();

        return true;
}

bool  GpuProgram::compileShaderFromString(const string &sourceCode, ShaderType::Enum type) {
        // Создаем шейдерный объект
        GLuint shader = 0;
        switch(type) {
                case ShaderType::VERTEX_SHADER:
                        m_log += "Loading vertex shader\n";
                        shader = glCreateShader(GL_VERTEX_SHADER);
                        m_vertexHandle = shader;
                        break;
                case ShaderType::FRAGMENT_SHADER:
                        m_log += "Loading fragment shader\n";
                        shader = glCreateShader(GL_FRAGMENT_SHADER);
                        m_fragmentHandle = shader;
                        break;
                case ShaderType::GEOMETRY_SHADER:
                        m_log += "Loading geometry shader\n";
                        shader = glCreateShader(GL_GEOMETRY_SHADER);
                        m_geometryHandle = shader;
                        break;
                case ShaderType::TESS_CONTROL_SHADER:
                        m_log += "Loading tesselation control shader\n";
                        shader = glCreateShader(GL_TESS_CONTROL_SHADER);
                        m_tessControlHandle = shader;
                        break;
                case ShaderType::TESS_EVAL_SHADER:
                        m_log += "Loading tesselation evaluation shader\n";
                        shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
                        m_tessEvalHandle = shader;
                        break;
                default:
                        m_log += "Wrong type of shader\n";
                        DEBUG("Wrong type of shader");
                        return false;
        }

        if(!shader) {
                DEBUG("Cannot create shader object");
                return false;
        }

        // Загружаем туда исходный код
        const GLchar *codeArray[] = { sourceCode.c_str() };
        glShaderSource(shader, 1, codeArray, NULL);

        // Компилируем шейдер
        glCompileShader(shader);

        int compileStatus;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus == GL_FALSE) {
                DEBUG("Cannot compile shader");
                m_log += "Cannot compile shader\n";

                // Получаем причину ошибки
                int logLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                if(logLength > 0) {
                        char *log = new char[logLength];
                        int written;
                        glGetShaderInfoLog(shader, logLength, &written, log);

                        m_log += log;
                        DEBUG(log);

                        delete [] log;
                }

                return false;
        } else {
                glAttachShader(m_programHandle, shader);

                DEBUG("Compille succeeded");
                m_log += "Compile succeeded\n";

                return true;
        }

}

bool GpuProgram::compileShaderFromFile(const string &filename, ShaderType::Enum type) {
        if (!createProgram()) return false;

        string sourceCode;
        if (!loadBufferFromFile(filename, &sourceCode)) return false;

        if (!compileShaderFromString(sourceCode, type)) return false;

        return true;
}

bool GpuProgram::link() {
        glLinkProgram(m_programHandle);

        int linkStatus;
        glGetProgramiv(m_programHandle, GL_LINK_STATUS, &linkStatus);
        if (linkStatus == GL_FALSE) {
                DEBUG("Cannot link program object");
                m_log += "Cannot link program object\n";

                int logLength = 0;
                glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &logLength);
                if (logLength > 0) {
                        char *log = new char[logLength];
                        int written = 0;
                        glGetProgramInfoLog(m_programHandle, logLength, &written, log);

                        m_log += log;
                        DEBUG(log);

                        delete [] log;
                }

                return false;
        } else {
                DEBUG("Link secceeded");
                m_log += "Link secceeded\n";
                m_isLinked = true;

                return true;
        }
}

bool GpuProgram::isLinked() {
        return m_isLinked;
}

bool GpuProgram::loadProgram(const string &filename) {
        if (!createProgram()) return false;

        //Загружает шейдеры из файла
        ifstream inFile(filename.c_str());
        if(!inFile) {
                DEBUG("Cannot open file");
                m_log += "Cannot open file\n";
                return false;
        }

        string vertexSource, fragmentSource, geometrySource, tessControlSource, tessEvalSource;
        string *current = NULL;

        string line;
        while(inFile) {
                std::getline(inFile, line);

                SHOW(line.substr(0,3));
                if(line.substr(0,3) == "//--") {
                        if(line.substr(4) == "VERTEX_SHADER") current = &vertexSource;
                        else if(line.substr(4) == "FRAGMENT_SHADER") current = &fragmentSource;
                        else if(line.substr(4) == "GEOMETRY_SHADER") current = &geometrySource;
                        else if(line.substr(4) == "TESS_CONTROL_SHADER") current = &tessControlSource;
                        else if(line.substr(4) == "TESS_EVAL_SHADER") current = &tessEvalSource;
                        break;
                }

                if(current != NULL) *current += line + '\n';
        }

        //Компилируем шейдеры, который получили
        if(!vertexSource.empty()) if(!compileShaderFromString(vertexSource, ShaderType::VERTEX_SHADER))  return false;
        if(!fragmentSource.empty()) if(!compileShaderFromString(fragmentSource, ShaderType::FRAGMENT_SHADER))  return false;
        if(!geometrySource.empty()) if(!compileShaderFromString(geometrySource, ShaderType::GEOMETRY_SHADER))  return false;
        if(!tessControlSource.empty()) if(!compileShaderFromString(tessControlSource, ShaderType::TESS_CONTROL_SHADER))  return false;
        if(!tessEvalSource.empty()) if(!compileShaderFromString(tessEvalSource, ShaderType::TESS_EVAL_SHADER))  return false;

        return true;
}

void GpuProgram::bind() {
        glUseProgram(m_programHandle);
}

void GpuProgram::unbind() {
        glUseProgram(0);
}

void GpuProgram::setUniform(const string &name, float value) {
        GLint loc = glGetUniformLocation(m_programHandle, name.c_str());
        glUniform1f(loc, value);
}

void GpuProgram::setUniform(const string &name, int value) {
        GLint loc = glGetUniformLocation(m_programHandle, name.c_str());
        glUniform1i(loc, value);
}

void GpuProgram::setUniform(const string &name, const vec3 &value) {
        GLint loc = glGetUniformLocation(m_programHandle, name.c_str());
        glUniform3f(loc, value.x, value.y, value.z);
}

void GpuProgram::setUniform(const string &name, const vec4 &value) {
        GLint loc = glGetUniformLocation(m_programHandle, name.c_str());
        glUniform4f(loc, value.x, value.y, value.z, value.z);
}

void GpuProgram::setUniform(const string &name, const mat3 &value) {
        GLint loc = glGetUniformLocation(m_programHandle, name.c_str());
        glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
}

void GpuProgram::setUniform(const string &name, const mat4 &value) {
        GLint loc = glGetUniformLocation(m_programHandle, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
}

GLuint GpuProgram::handle() const {
        return m_programHandle;
}

string GpuProgram::getLog() {
        return m_log;
}

void GpuProgram::showLog() {
        std::cout << m_log << std::endl;
}

void GpuProgram::showActiveUniforms() {
        GLint countUniforms, maxLength, size, location;
        GLsizei written;
        GLenum type;
        GLchar *name;

        glGetProgramiv(m_programHandle, GL_ACTIVE_UNIFORMS, &countUniforms);
        glGetProgramiv(m_programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
        name = new GLchar[maxLength];

        std::cout << "Location\t | Name" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
        for(int i=0; i < countUniforms; ++i) {
                glGetActiveUniform(m_programHandle, i, maxLength, &written, &size, &type, name);
                location = glGetUniformLocation(m_programHandle, name);
                std::cout << location << "\t\t | " << name << std::endl;
        }

        delete [] name;
}

void GpuProgram::showActiveAttributes() {
        GLint countAttribs, maxLength, size, location;
        GLsizei written;
        GLenum type;
        GLchar *name;

        glGetProgramiv(m_programHandle, GL_ACTIVE_ATTRIBUTES, &countAttribs);
        glGetProgramiv(m_programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
        name = new GLchar[maxLength];

        std::cout << "Location\t | Name" << std::endl;
        std::cout << "-------------------------------------------------------------------------------------" << std::endl;
        for(int i=0; i < countAttribs; ++i) {
                glGetActiveAttrib(m_programHandle, i, maxLength, &written, &size, &type, name);
                location = glGetAttribLocation(m_programHandle, name);
                std::cout << location << "\t | " << name << std::endl;
        }

        delete [] name;
}
