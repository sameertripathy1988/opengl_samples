#pragma once
#include <glew.h>
#include <map>
#include <string>
#include "ThirdParty/SOIL.h"
#include <iostream>
#include "Util.h"

class TextureManager {
private:
	TextureManager(){}
	~TextureManager() {
		clearTextures();
	}
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator =(const TextureManager&) = delete;
	std::map<std::string, GLuint> textures;

public:
	static TextureManager& getInstance()
	{
		static TextureManager instance;
		return instance;
	}
    GLuint loadTexture(const std::string& filePath) {
        if (textures.find(filePath) != textures.end()) {
            return textures[filePath];
        }

        GLuint textureID = Util::loadTexture(filePath);

        if (textureID == 0) {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
        }

        textures[filePath] = textureID;
        return textureID;
    }

    void unloadTexture(const std::string& filePath) {
        auto it = textures.find(filePath);
        if (it != textures.end()) {
            glDeleteTextures(1, &it->second);
            textures.erase(it);
        }
    }

    void clearTextures() {
        for (auto& texture : textures) {
            glDeleteTextures(1, &texture.second);
        }
        textures.clear();
    }
};