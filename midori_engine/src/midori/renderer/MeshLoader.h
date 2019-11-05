// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: MeshLoader.h
// Date: 05/11/2019

#pragma once

#include "midori/renderer/VertexArray.h"

#include <string>

namespace midori {

    class MeshLoader {
    public:
        static ref<VertexArray> Load(const std::string& path);
    };
    
}
