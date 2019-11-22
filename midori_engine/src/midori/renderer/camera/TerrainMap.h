// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: TerrainMap.h
// Date: 22/11/2019

#pragma once

#include "midori/renderer/Texture.h"
#include "midori/renderer/Buffer.h"

namespace midori {

    class TerrainMap {
    public:
        TerrainMap();
        ~TerrainMap();



    private:
        ref<FrameBufferColorCube> m_FrameBuffer;
        ref<TextureCubeMap> m_CubeMap;
    };

}
