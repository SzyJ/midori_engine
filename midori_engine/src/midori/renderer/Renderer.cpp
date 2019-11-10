// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Renderer.cpp
// Date: 29/10/2019

#include "mdpch.h"
#include "Renderer.h"

namespace midori {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(Camera* camera) {
        m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();

        RenderCommand::DrawVertices(vertexArray);
    }

    void Renderer::SubmitPatches(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform, uint32_t vertices) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();

        RenderCommand::DrawPatches(vertexArray, vertices);
    }


}
