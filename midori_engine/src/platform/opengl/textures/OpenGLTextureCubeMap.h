// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLTextureCubeMap.h
// Date: 11/11/2019

#pragma once

#include "midori/renderer/Texture.h"

namespace midori {

    class OpenGLTextureCubeMap : public TextureCubeMap {
    public:
        OpenGLTextureCubeMap() = delete;
        OpenGLTextureCubeMap(const std::string& path);
        virtual ~OpenGLTextureCubeMap();

        virtual void Bind(const uint32_t slot = 0) const override;

    private:
        std::string m_Path;

        uint32_t m_ImagesID;

        inline static void BindTextureData(char* pathToImage, char* const extPtr, const char* faceExtention, uint32_t textureTarget);
    };

}
