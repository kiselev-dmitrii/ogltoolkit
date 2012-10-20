#include "BufferObject.h"
#include "lib/Debug/Debug.h"

BufferObject::BufferObject(Target::Enum target) {
        glGenBuffers(1, &m_handle);
        m_target = target;                      //таргет по умолчанию
}

BufferObject::~BufferObject() {
        glDeleteBuffers(1, &m_handle);
}

void BufferObject::setTarget(Target::Enum target) {
        m_target = target;
}

void BufferObject::uploadData(void *data, GLsizeiptr dataSize, Hint::Enum hint) {
        glBindBuffer(m_target, m_handle);
        glBufferData(m_target, dataSize, data, hint);
        glBindBuffer(m_target, 0);
}

void BufferObject::updateData(void *data, GLsizeiptr dataSize, GLintptr startPos) {
        glBindBuffer(m_target, m_handle);
        glBufferSubData(m_target, startPos, dataSize, data);
        glBindBuffer(m_target, 0);
}

void BufferObject::bind() {
        glBindBuffer(m_target, m_handle);
}

void BufferObject::unbind() {
        glBindBuffer(m_target, 0);
}

void *BufferObject::map(Access::Enum access) {
        glBindBuffer(m_target, m_handle);
        return glMapBuffer(m_target, access);
}

void BufferObject::unmap() {
        if(glUnmapBuffer(m_target) == GL_FALSE) DEBUG("Cannot unmap buffer");
}

void BufferObject::copyFrom(const BufferObject &readBuf, GLintptr readStart, GLintptr writeStart, GLsizeiptr size) {
        glBindBuffer(GL_COPY_READ_BUFFER, readBuf.handle());
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_handle);

        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER,  readStart, writeStart, size);

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

GLuint BufferObject::handle() const {
        return m_handle;
}
