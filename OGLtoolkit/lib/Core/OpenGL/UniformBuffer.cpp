#include "UniformBuffer.h"
#include "string.h"

UniformBlock::UniformBlock(GpuProgram *program, const string &blockName) {
        // Получаем индекс блока
        m_programHandle = program->handle();
        m_blockIndex = glGetUniformBlockIndex(m_programHandle, blockName.c_str());

        //Выделяем память под данные блока
        glGetActiveUniformBlockiv(m_programHandle, m_blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &m_dataSize);
        m_data = new GLubyte [m_dataSize];
}

UniformBlock::~UniformBlock() {
        delete m_data;
}

void UniformBlock::copyValueToArray(const string &memberName, const void *value, size_t valueSize) {
        //Получаем индекс поля внутри блока
        GLuint index;
        const GLchar *names[] = { memberName.c_str() };
        glGetUniformIndices(m_programHandle, 1, names, &index);

        // Вычисляем смещение в массиве m_data, где будут храниться байты поля
        GLint offset;
        glGetActiveUniformsiv(m_programHandle, 1, &index, GL_UNIFORM_OFFSET, &offset);

        // Копируем данные в массив m_data
        memcpy(m_data + offset, value, valueSize);

}

void UniformBlock::setMember(const string &name, float value) {
        copyValueToArray(name, &value, sizeof(float));
}

void UniformBlock::setMember(const string &name, int value) {
        copyValueToArray(name, &value, sizeof(int));
}

void UniformBlock::setMember(const string &name, const vec3 &value) {
        copyValueToArray(name, &value[0], 3*sizeof(float));
}

void UniformBlock::setMember(const string &name, const vec4 &value) {
        copyValueToArray(name, &value[0], 4*sizeof(float));
}

void UniformBlock::setMember(const string &name, const mat3 &value) {
        copyValueToArray(name, &value[0][0], 9*sizeof(float));
}

void UniformBlock::setMember(const string &name, const mat4 &value) {
        copyValueToArray(name, &value[0][0], 16*sizeof(float));
}

GLubyte* UniformBlock::data() const {
        return m_data;
}

GLint UniformBlock::size() const {
        return m_dataSize;
}

GLuint UniformBlock::index() const {
        return m_blockIndex;
}

//=======================================================================//

UniformBuffer::UniformBuffer() : BufferObject(Target::UNIFORM_BUFFER) {
}

void UniformBuffer::uploadData(UniformBlock *dataBlock, Hint::Enum hint) {
        BufferObject::uploadData(dataBlock->data(), dataBlock->size(), hint);
}

void UniformBuffer::bindToBlock(GLuint blockIndex) {
        glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, m_handle);
}

void UniformBuffer::bindToBlock(UniformBlock *block) {
        glBindBufferBase(GL_UNIFORM_BUFFER, block->index(), m_handle);
}
