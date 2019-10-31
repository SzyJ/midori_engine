// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Renderer.h
// Date: 29/10/2019

#pragma once

#include "midori/renderer/camera/Camera.h"
#include "midori/renderer/RenderCommand.h"
#include "midori/renderer/Shader.h"

namespace midori {

    class Renderer {
    public:
        static void BeginScene(Camera* camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };

}
