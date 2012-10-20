#ifndef UNIFORMBUFFER_H
#define UNIFORMBUFFER_H

#include "GpuProgram.h"
#include "BufferObject.h"

/** Класс, представляющий собой UniformBlock.
    Данные хранятся внутри объекта (в RAM, а не в VideoMemory)
  */
class UniformBlock {
private:
        GLuint          m_blockIndex;           //индекс блока
        GLuint          m_programHandle;        //программа с которым связан блок

        GLubyte*        m_data;                 //данные, назодящиеся в uniform-блоке
        GLint           m_dataSize;             //размер блока
private:
        // Копирует данные в массив m_data в соответствии со смещением
        void            copyValueToArray(const string &memberName, const void *value, size_t valueSize);
public:
        UniformBlock(GpuProgram *program, const string &blockName);
        ~UniformBlock();

        // Устанавливает переменную из блока
        void            setMember(const string &name, float value);
        void            setMember(const string &name, int value);
        void            setMember(const string &name, const vec3 &value);
        void            setMember(const string &name, const vec4 &value);
        void            setMember(const string &name, const mat3 &value);
        void            setMember(const string &name, const mat4 &value);

        // Возвращает указатель на массив данных блока
        GLubyte*        data() const;
        // Возвращает размер блока в байтах
        GLint           size() const;

        //Возвращает индекс данного блока
        GLuint          index() const;
};

/** Класс-обертка для UniformBufferObject
  */
class UniformBuffer : public BufferObject {
public:
        // Создает UBO
        UniformBuffer();

        // Загружает данные блока в UBO
        void uploadData(UniformBlock *dataBlock, Hint::Enum hint);

        // Привязывает данные к конкретному блоку
        // На самом деле в таргете GL_UNIFORM_BUFFER есть индексы, которые соответствую блокам
        // Таким образом, осущесвляется и привязка к таргету
        void bindToBlock(GLuint blockIndex);
        void bindToBlock(UniformBlock *block);
};

#endif // UNIFORMBUFFER_H
