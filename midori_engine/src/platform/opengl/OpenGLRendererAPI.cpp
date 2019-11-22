// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLRendererAPI.cpp
// Date: 31/10/2019

#include "mdpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace midori {

    void OpenGLRendererAPI::Init() {
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetDebugMode(const bool debugModeState) {
        glPolygonMode(GL_FRONT_AND_BACK, debugModeState ? GL_LINE : GL_FILL);
    }

    void OpenGLRendererAPI::SetDepthMask(const bool newState) {
        glDepthMask(newState ? GL_TRUE : GL_FALSE);
    }

    void OpenGLRendererAPI::DrawVertices(const ref<VertexArray>& vertexArray) {
        if (vertexArray->GetIndexBuffer()) {
            glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        } else {
            for (const auto& vertexBuffer : vertexArray->GetVertexBuffers()) {
                glDrawArrays(GL_TRIANGLES, 0, vertexBuffer->GetSize());
            }
        }
    }

    void OpenGLRendererAPI::DrawPatches(const ref<VertexArray>& vertexArray, uint32_t verticesPerPatch) {
        glPatchParameteri(GL_PATCH_VERTICES, verticesPerPatch);

        if (vertexArray->GetIndexBuffer()) {
            glDrawElements(GL_PATCHES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        } else {
            for (const auto& vertexBuffer : vertexArray->GetVertexBuffers()) {
                glDrawArrays(GL_PATCHES, 0, vertexBuffer->GetSize());
            }
        }
    }

    void OpenGLRendererAPI::SetViewport(const int xOffset, const int yOffset, const int width, const int height) {
        glViewport(xOffset, yOffset, width, height);
    }

    void OpenGLRendererAPI::SetActiveTexture(uint8_t textureSlot) {
        glActiveTexture(GL_TEXTURE0 + textureSlot);
    }

}
