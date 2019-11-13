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
        m_SceneData->ProjectionMatrix = camera->GetProjectionMatrix();
        m_SceneData->StaticViewMatrix = glm::mat4(glm::mat3(camera->GetViewMatrix()));

        m_SceneData->CameraPosition = camera->GetPosition();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform, const Material& material) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Projection", m_SceneData->ProjectionMatrix);
        shader->UploadUniformMat4("u_StaticView", m_SceneData->StaticViewMatrix);
        shader->UploadUniformMat4("u_Transform", transform);
        shader->UploadUniformFloat3("u_CameraPos", m_SceneData->CameraPosition);

        if (m_SceneData->Lights) {
            shader->UploadUniformFloat3("u_LightPos", m_SceneData->Lights->GetPointLights().at(0)->Position);
            shader->UploadUniformFloat3("u_LightCol", m_SceneData->Lights->GetPointLights().at(0)->Color);
        }

        shader->UploadUniformFloat3("u_Material.ambient", material.ambient);
        shader->UploadUniformFloat3("u_Material.diffuse", material.diffuse);
        shader->UploadUniformFloat3("u_Material.specular", material.specular);
        shader->UploadUniformFloat("u_Material.shininess", material.shininess);

        vertexArray->Bind();

        RenderCommand::DrawVertices(vertexArray);
    }

    void Renderer::Submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const Material& material) {
        Submit(shader, vertexArray, glm::mat4(1.0f), material);
    }

    void Renderer::SubmitPatches(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform, uint32_t vertices) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();

        RenderCommand::DrawPatches(vertexArray, vertices);
    }


}
