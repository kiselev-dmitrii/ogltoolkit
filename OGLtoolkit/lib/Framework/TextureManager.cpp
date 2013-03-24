#include "TextureManager.h"
#include "lib/Utils/Debug.h"

TextureManager::TextureManager() { }

TextureManager::~TextureManager() {
        removeAllTextures();
}

TextureManager* TextureManager::instance() {
        static TextureManager instance;
        return &instance;
}

ColorTexture2D* TextureManager::addColorTexture2D(const string &textureName, ColorTexture2D *texture) {
        m_textures.insert(std::pair<string, Texture*>(textureName, texture));
        return texture;
}

DepthTexture2D* TextureManager::addDepthTexture2D(const string &textureName, DepthTexture2D *texture) {
        m_textures.insert(std::pair<string, Texture*>(textureName, texture));
        return texture;
}

TextureCube* TextureManager::addTextureCube(const string &textureName, TextureCube *texture) {
        m_textures.insert(std::pair<string, Texture*>(textureName, texture));
        return texture;
}

void TextureManager::removeTexture(const string &textureName) {
        MapTexture::iterator it;
        it = m_textures.find(textureName);

        if(it != m_textures.end()) {
                delete it->second;
                m_textures.erase(it);
        } else {
                DEBUG("Error on removing: texture with name " << textureName << " not exist");
        }
}

void TextureManager::removeAllTextures() {
        MapTexture::iterator it;
        for(it = m_textures.begin(); it != m_textures.end(); ++it) {
                delete it->second;
        }
        m_textures.erase(m_textures.begin(), m_textures.end());
}

Texture* TextureManager::texture(const string &textureName) const {
        MapTexture::const_iterator it;
        it = m_textures.find(textureName);

        if(it != m_textures.end()) {
                return it->second;
        } else {
                DEBUG("Error on finding: texture with name " << textureName << " not exist");
                return NULL;
        }
}

StringList TextureManager::listOfTextures() const {
        StringList result;

        MapTexture::const_iterator it;
        for(it = m_textures.begin(); it != m_textures.end(); ++it) {
                result.push_back(it->first);
        }

        return result;
}
