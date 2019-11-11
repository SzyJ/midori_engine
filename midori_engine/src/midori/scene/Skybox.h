// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Skybox.h
// Date: 11/11/2019

#pragma once

#include "midori/renderer/Texture.h"
#include "midori/renderer/Shader.h"

namespace midori {

    class Skybox {
    public:
        Skybox();
        ~Skybox();

        void Draw();

    private:
        ref<TextureCubeMap> m_CubeMap;
        ref<Shader> m_Shader;
    };

}
