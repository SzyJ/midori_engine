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
        //TODO: Remove below code [DEBUG]
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void OpenGLRendererAPI::DrawVertices(const ref<VertexArray>& vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::SetViewport(const int xOffset, const int yOffset, const int width, const int height) {
        glViewport(xOffset, yOffset, width, height);
    }

}
