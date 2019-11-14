// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Renderer.cpp
// Date: 29/10/2019

#include "mdpch.h"
#include "Renderer.h"

#include <glm/gtc/type_ptr.hpp>

namespace midori {

    const static BufferLayout s_CamDataLayout = BufferLayout({
        {ShaderDataType::Mat4, "ViewProjection"},
        {ShaderDataType::Float3, "Position"},
        {ShaderDataType::Float, "Padding"},
        {ShaderDataType::Mat4, "Projection"},
        {ShaderDataType::Mat4, "StaticView"}
    });

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
    Renderer::Uniforms* Renderer::m_Uniforms = new Renderer::Uniforms;

    void Renderer::BeginScene(Camera* camera) {
        m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
        m_SceneData->CameraPosition = camera->GetPosition();

        m_SceneData->ProjectionMatrix = camera->GetProjectionMatrix();
        m_SceneData->StaticViewMatrix = glm::mat4(glm::mat3(camera->GetViewMatrix()));

        if (!m_Uniforms->Camera) {
            m_Uniforms->Camera = UniformBuffer::Create(s_CamDataLayout.GetStride(), nullptr);
            m_Uniforms->Camera->SetLayout(s_CamDataLayout);
        }

        float paddingData = 0.0f;
        m_Uniforms->Camera->SetSubData(0, glm::value_ptr(m_SceneData->ViewProjectionMatrix));
        m_Uniforms->Camera->SetSubData(1, glm::value_ptr(m_SceneData->CameraPosition));
        m_Uniforms->Camera->SetSubData(2, &paddingData);
        m_Uniforms->Camera->SetSubData(3, glm::value_ptr(m_SceneData->ProjectionMatrix));
        m_Uniforms->Camera->SetSubData(4, glm::value_ptr(m_SceneData->StaticViewMatrix));
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
