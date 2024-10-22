// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: RendererAPI.h
// Date: 31/10/2019

#pragma once

#include "midori/renderer/VertexArray.h"
#include <glm/glm.hpp>

namespace midori {

    class RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1
        };

        RendererAPI() = default;
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void SetDebugMode(const bool debugModeState) = 0;
        virtual void SetDepthMask(const bool newState) = 0;
        virtual void SetDepthTest(const bool newState) = 0;

        virtual void DrawVertices(const ref<VertexArray>& vertexArray) = 0;
        virtual void DrawPatches(const ref<VertexArray>& vertexArray, uint32_t verticesPerPatch) = 0;

        virtual void SetViewport(const int xOffset, const int yOffset, const int width, const int height) = 0;

        virtual void SetActiveTexture(uint8_t textureSlot) = 0;

        inline static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };

}
