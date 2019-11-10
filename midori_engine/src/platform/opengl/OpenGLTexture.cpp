// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLTexture.cpp
// Date: 02/11/2019

#include "mdpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace midori {

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_ImagesID);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        : m_Path(path) {
        int width, height, channelCount;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* imageData = stbi_load(path.c_str(), &width, &height, &channelCount, 0);
        MD_CORE_ASSERT(imageData, "Failed to load image: {0}", path);

        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;

        switch (channelCount) {
        case 4:
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
            break;
        case 3:
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
            break;
        case 1:
            internalFormat = GL_RED;
            dataFormat = GL_R8;
            break;
        default:
            MD_CORE_ERROR("Attempt to load texture of unsupported format: {0}", path);
            MD_CORE_ERROR("Channel count: {0}", channelCount);
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_ImagesID);
        glTextureStorage2D(m_ImagesID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_ImagesID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_ImagesID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_ImagesID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, imageData);

        stbi_image_free(imageData);
    }

    void OpenGLTexture2D::Bind(const uint32_t slot) const {
        glBindTextureUnit(slot, m_ImagesID);
    }

}
