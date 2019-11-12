// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Texture.h
// Date: 02/11/2019

#pragma once

#include "midori/core/Core.h"

#include <string>

namespace midori {

    class Texture {
    public:

        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(const uint32_t slot = 0) const = 0;

    };

    class Texture2D : public Texture {
    public:
        static ref<Texture2D> Create(const std::string& path);
    };

    class TextureCubeMap : public Texture {
    public:
        static ref<TextureCubeMap> Create(const std::string& path);

        virtual void GetBindLocation(uint32_t& bindLocation) const = 0;
    };
}