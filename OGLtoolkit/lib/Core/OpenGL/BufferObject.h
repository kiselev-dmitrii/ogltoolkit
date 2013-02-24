#ifndef BUFFEROBJECT_H
#define BUFFEROBJECT_H

#include <string>
#include <GL/glew.h>

using std::string;

/** Вспомогательная информация, которая помогает OpenGL эффективно
    использовать BO в плане производительности
  */
namespace Hint {
enum Enum {
        // STATIC - данные будут установленны в буфер один раз и не изменятся
        STATIC_DRAW = GL_STATIC_DRAW,           // DRAW - только для записи пользователем
        STATIC_READ = GL_STATIC_READ,           // READ - только для чтения пользователем
        STATIC_COPY = GL_STATIC_COPY,           // COPY - чтение/запись
        // DYNAMIC - данные будут периодически изменятся
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        DYNAMIC_READ = GL_DYNAMIC_READ,
        DYNAMIC_COPY = GL_DYNAMIC_COPY,
        // STREAM - данные будут изменятся каждый кадр
        STREAM_DRAW = GL_STREAM_DRAW,
        STREAM_READ = GL_STREAM_READ,
        STREAM_COPY = GL_STREAM_COPY
};
}

/** Точка привязки буфера
  */
namespace Target {
enum Enum {
        ARRAY_BUFFER = GL_ARRAY_BUFFER,
        UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
        ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER
};
}

/** Определяет доступ пользователя к BO
  */
namespace Access {
enum Enum {
        READ_ONLY = GL_READ_ONLY,
        WRITE_ONLY = GL_WRITE_ONLY,
        READ_WRITE = GL_READ_WRITE
};
}

/** Базовый класс для BufferObject.
    От него наследуется VertexBuffer, UniformBuffer, IndexBuffer
  */
class BufferObject {
protected:
        GLuint          m_handle;               //дескриптор буфера
        Target::Enum    m_target;               //точка привязки буфера
public:
        // Создает экземпляр BO
        BufferObject(Target::Enum target);
        // Удаляет BO
        ~BufferObject();

        //Устанавливает таргет, с которым будут осуществлятся операции (бинд и т.д)
        void setTarget(Target::Enum target);

        // Загружает данные data, размера dataSize, в буффер
        // access определяет доступ юзера к данным, freq - частоту использования данных
        // При использовании более одного раза, данные будут выделены в другом месте.
        // Для обновления данных используйте updateData
        void uploadData(void *data, GLsizeiptr dataSize, Hint::Enum hint);

        // Обновляет часть данных из массива data, размера dataSize
        // Перезаписывает данные, начиная с позиции startPos
        void updateData(void *data, GLsizeiptr dataSize, GLintptr startPos);

        // Привязывает буфер к текущему таргету (выбранному в setTarget, или указанному в конструкторе
        void bind();
        // Отвязывает BO
        void unbind();

        // Включить отображение(mapping) для данного буфера
        // Возвращает ссылку на данные, хранящиеся в буфере, так что можно работать как с обычными данными
        void *map(Access::Enum access);
        // Выключает отображение. Указатель на данные становится недействительным
        // Возвращает false в случае неудачи
        void unmap();

        // Копирует данные из другого буфера в данный
        void copyFrom(const BufferObject &readBuf, GLintptr readStart, GLintptr writeStart, GLsizeiptr size);

        //Возвращает идентификатор буфера
        GLuint handle() const;
};

#endif // BUFFEROBJECT_H
