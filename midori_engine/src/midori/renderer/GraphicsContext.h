// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: GraphicsContext.h
// Date: 10/10/2019

#pragma once

namespace midori {

    class GraphicsContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}
