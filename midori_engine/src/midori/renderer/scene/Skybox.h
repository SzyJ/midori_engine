// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Skybox.h
// Date: 11/11/2019

#pragma once

#include "midori/renderer/Texture.h"
#include "midori/renderer/Shader.h"
#include "midori/renderer/VertexArray.h"

#define MD_CUBEMAP_TEXTURE_SLOT 30

namespace midori {

    class Skybox {
    public:
        Skybox() = delete;
        Skybox(const std::string& texturePath);
        ~Skybox();

        void Draw();

        static ref<Skybox> Create(const std::string& texturePath);

    private:
        ref<TextureCubeMap> m_CubeMap;
        ref<Shader> m_Shader;
        ref<VertexArray> m_VertexArray;
        glm::vec3 m_LookLocation;

    };

}
