// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLTextureCubeMap.cpp
// Date: 11/11/2019

#include "mdpch.h"
#include "OpenGLTextureCubeMap.h"

#include <glad/glad.h>
#include <stb_image.h>

#define MD_FILEPATH_MAX 255

#ifndef MD_CM_FRONT_EXT
#define MD_CM_FRONT_EXT "_Front.png"
#endif

#ifndef MD_CM_BACK_EXT
#define MD_CM_BACK_EXT "_Back.png"
#endif

#ifndef MD_CM_LEFT_EXT
#define MD_CM_LEFT_EXT "_Left.png"
#endif

#ifndef MD_CM_RIGHT_EXT
#define MD_CM_RIGHT_EXT "_Right.png"
#endif

#ifndef MD_CM_UP_EXT
#define MD_CM_UP_EXT "_Up.png"
#endif

#ifndef MD_CM_DOWN_EXT
#define MD_CM_DOWN_EXT "_Down.png"
#endif

namespace midori {

    OpenGLTextureCubeMap::~OpenGLTextureCubeMap() {
        glDeleteTextures(1, &m_ImagesID);
    }

    OpenGLTextureCubeMap::OpenGLTextureCubeMap(const std::string& path) {
        glGenTextures(1, &m_ImagesID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_ImagesID);

        char thisPath[MD_FILEPATH_MAX];
        std::strcpy(thisPath, path.c_str());
        char* const extPtr = thisPath + path.length();

        BindTextureData(thisPath, extPtr, MD_CM_RIGHT_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        BindTextureData(thisPath, extPtr, MD_CM_LEFT_EXT, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        BindTextureData(thisPath, extPtr, MD_CM_UP_EXT, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        BindTextureData(thisPath, extPtr, MD_CM_DOWN_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        BindTextureData(thisPath, extPtr, MD_CM_BACK_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        BindTextureData(thisPath, extPtr, MD_CM_FRONT_EXT, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    OpenGLTextureCubeMap::OpenGLTextureCubeMap() {
        glGenTextures(1, &m_ImagesID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_ImagesID);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void OpenGLTextureCubeMap::Bind(const uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_ImagesID);
    }

    inline void OpenGLTextureCubeMap::BindTextureData(char* pathToImage, char* const extPtr, const char* faceExtention, GLuint textureTarget) {
        int width, height, channelCount;
        
        std::strcpy(extPtr, faceExtention);
        
        stbi_uc* imageData = stbi_load(pathToImage, &width, &height, &channelCount, 0);
        if (imageData) {
            glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            stbi_image_free(imageData);
        } else {
            MD_CORE_ERROR("Cube Map texture could not be loaded: {0}", pathToImage);
        }
    }

}
