// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLRendererAPI.h
// Date: 31/10/2019

#pragma once

#include "midori/renderer/RendererAPI.h"

namespace midori {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        OpenGLRendererAPI() = default;
        ~OpenGLRendererAPI() = default;

        virtual void Init() override;

        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawVertices(const ref<VertexArray>& vertexArray) override;

        virtual void SetViewport(const int xOffset, const int yOffset, const int width, const int height) override;
    };

}
