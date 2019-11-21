// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: RenderCommand.h
// Date: 31/10/2019

#pragma once

#include "midori/renderer/RendererAPI.h"

namespace midori {

    class RenderCommand {
    public:
        inline static void Init() {
            s_RendererAPI->Init();
        }

        inline static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear() {
            s_RendererAPI->Clear();
        }

        inline static void SetDebugMode(const bool debugModeState) {
            s_RendererAPI->SetDebugMode(debugModeState);
        }

        inline static void SetDepthMask(const bool newState) {
            s_RendererAPI->SetDepthMask(newState);
        }

        inline static void DrawVertices(const ref<VertexArray>& vertexArray) {
            s_RendererAPI->DrawVertices(vertexArray);
        }

        inline static void DrawPatches(const ref<VertexArray>& vertexArray, uint32_t indicesInVertex) {
            s_RendererAPI->DrawPatches(vertexArray, indicesInVertex);
        }

        inline static void SetViewport(const int xOffset, const int yOffset, const int width, const int height) {
            s_RendererAPI->SetViewport(xOffset, yOffset, width, height);
        }

        inline static void SetActiveTexture0() {
            s_RendererAPI->SetActiveTexture0();
        }

        inline static void SetActiveTexture1() {
            s_RendererAPI->SetActiveTexture1();
        }


    private:
        static RendererAPI* s_RendererAPI;
    };

}
