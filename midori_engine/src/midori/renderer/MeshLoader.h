// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: MeshLoader.h
// Date: 05/11/2019

#pragma once

#include "midori/renderer/VertexArray.h"

#include <string>

namespace midori {

    enum class MeshLoadedData {
        none = 0,

        p = 1,
        n = 2,
        t = 4,

        pn = 3,
        pt = 5,

        pnt = 7
    };

    class MeshLoader {
    public:
        static ref<VertexArray> Load(const std::string& path);

    private:

    };
    
}
