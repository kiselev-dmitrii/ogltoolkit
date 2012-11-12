#include "TextureUnit.h"

int TextureUnit::m_counter = 0;

TextureUnit::TextureUnit() {
        m_number = m_counter;
        ++m_counter;
}

TextureUnit::~TextureUnit() {
        --m_counter;
}

void TextureUnit::bind() {
        glActiveTexture(GL_TEXTURE0 + m_number);
}

int TextureUnit::number() {
        return m_number;
}
