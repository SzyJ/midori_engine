// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLTexture.cpp
// Date: 02/11/2019

#pragma once

#include "midori/renderer/Texture.h"

namespace midori {

    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D() = delete;
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }

        virtual void Bind(const uint32_t slot = 0) const override;

    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_ImagesID;
    };

}
