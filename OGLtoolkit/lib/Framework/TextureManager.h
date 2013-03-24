#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>
#include <map>
#include "lib/Core/OpenGL/Texture2D.h"
#include "lib/Core/OpenGL/TextureCube.h"

typedef vector<string> StringList;
typedef map<string, Texture*> MapTexture;


/** Класс, служащий для управления текстурами
  * Содержит методы для добавления, создания, удаления и получения загруженных текстур
  */
class TextureManager {
private:
        MapTexture      m_textures;

private:
        // Закрытые конструкторы
        TextureManager();
        TextureManager(const TextureManager&);
        TextureManager& operator=(const TextureManager&);

public:
        // Точка доступа
        static TextureManager* instance();
        // Деструктор
        ~TextureManager();

        // Добавляет текстуру
        ColorTexture2D* addColorTexture2D(const string& textureName, ColorTexture2D* texture);
        DepthTexture2D* addDepthTexture2D(const string& textureName, DepthTexture2D* texture);
        TextureCube*    addTextureCube(const string& textureName, TextureCube* texture);

        // Удаляет текстуру
        void            removeTexture(const string& textureName);
        void            removeAllTextures();

        // Возвращает текстуру по имени (приведение делать вручную)
        Texture*        texture(const string& textureName) const;

        // Возвращает список управляемых текстур
        StringList      listOfTextures() const;

};

#endif // TEXTUREMANAGER_H
