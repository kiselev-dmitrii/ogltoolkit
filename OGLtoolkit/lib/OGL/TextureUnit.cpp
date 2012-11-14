#include "TextureUnit.h"
#include "lib/Debug/Debug.h"

int TextureUnit::m_countUsed = 0;
vector<bool> TextureUnit::m_usedUnits;

int TextureUnit::assignUnit() {
        //Проверяем, можем ли мы выделить еще один TIU
        if(m_countUsed==GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
                DEBUG("Cannot assign new Texture Image Unit");
                return 0;
        }

        // Ищем свободный
        for (size_t i=0; i<m_usedUnits.size(); ++i) {
                if (!m_usedUnits[i]) {
                        m_usedUnits[i] = true;
                        ++m_countUsed;
                        return i;
                }
        }

        //Свободный не нашли, выделяем новый
        m_usedUnits.push_back(true);
        ++m_countUsed;
        return m_usedUnits.size()-1;
}

void TextureUnit::freeUnit(int i) {
        m_usedUnits[i] = false;
        --m_countUsed;
}

TextureUnit::TextureUnit() {
        m_number = assignUnit();
}

TextureUnit::~TextureUnit() {
        freeUnit(m_number);
}

void TextureUnit::bind() {
        glActiveTexture(GL_TEXTURE0 + m_number);
}

int TextureUnit::number() {
        return m_number;
}