// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Renderer.h
// Date: 29/10/2019

#pragma once

namespace midori {

    enum class RendererAPI {
        None = 0,
        OpenGL = 1
    };

    class Renderer {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }

    private:
        static RendererAPI s_RendererAPI;
    };

}
