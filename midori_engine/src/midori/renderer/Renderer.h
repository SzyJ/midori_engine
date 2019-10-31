// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Renderer.h
// Date: 29/10/2019

#pragma once
#include "midori/renderer/RenderCommand.h"

namespace midori {

    class Renderer {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };

}
