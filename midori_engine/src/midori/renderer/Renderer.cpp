// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Renderer.cpp
// Date: 29/10/2019

#include "mdpch.h"
#include "Renderer.h"

#include <glm/gtc/type_ptr.hpp>

#define MD_MAX_POINT_LIGHTS 70
#define MD_MAX_DIR_LIGHTS 10
#define MD_MAX_SPOT_LIGHTS 10

namespace midori {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
    Renderer::Uniforms* Renderer::m_Uniforms = new Renderer::Uniforms;

    const BufferLayout Renderer::c_CamDataLayout = BufferLayout({
        {ShaderDataType::Mat4, "ViewProjection"},
        {ShaderDataType::Float3, "Position"},
        {ShaderDataType::Float, "Padding"},
        {ShaderDataType::Mat4, "Projection"},
        {ShaderDataType::Mat4, "StaticView"}
    });

    void Renderer::BeginScene(Camera* camera) {
        m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
        m_SceneData->CameraPosition = camera->GetPosition();

        m_SceneData->ProjectionMatrix = camera->GetProjectionMatrix();
        m_SceneData->StaticViewMatrix = glm::mat4(glm::mat3(camera->GetViewMatrix()));

        PopulateCameraUniforms();
        PopulatePointLightUniforms();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform, const Material& material) {
        shader->Bind();

        m_Uniforms->Camera->Bind();
        shader->BindUniformBuffer("MVP", c_CameraDataBindingBlock);

        if (m_Uniforms->AllLights) {
            m_Uniforms->AllLights->Bind();
            shader->BindUniformBuffer("Lights", c_PointLightDataBindingBlock);
        }

        shader->UploadUniformMat4("u_Transform", transform);

        //if (m_SceneData->Lights) {
        //    shader->UploadUniformFloat3("u_LightPos", m_SceneData->Lights->GetPointLights().at(0)->Position);
        //    shader->UploadUniformFloat3("u_LightCol", m_SceneData->Lights->GetPointLights().at(0)->Color);
        //}

        shader->UploadUniformFloat3("u_Material.Ambient", material.ambient);
        shader->UploadUniformFloat3("u_Material.Diffuse", material.diffuse);
        shader->UploadUniformFloat3("u_Material.Specular", material.specular);
        shader->UploadUniformFloat("u_Material.Shininess", material.shininess);

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

    void Renderer::PopulateCameraUniforms() {
        if (!m_Uniforms->Camera) {
            m_Uniforms->Camera = UniformBuffer::Create(c_CamDataLayout.GetStride(), nullptr, c_CameraDataBindingBlock);
            m_Uniforms->Camera->SetLayout(c_CamDataLayout);
        }

        m_Uniforms->Camera->Bind();

        float paddingData = 0.0f;
        m_Uniforms->Camera->SetSubData(0, glm::value_ptr(m_SceneData->ViewProjectionMatrix));
        m_Uniforms->Camera->SetSubData(1, glm::value_ptr(m_SceneData->CameraPosition));
        m_Uniforms->Camera->SetSubData(2, &paddingData);
        m_Uniforms->Camera->SetSubData(3, glm::value_ptr(m_SceneData->ProjectionMatrix));
        m_Uniforms->Camera->SetSubData(4, glm::value_ptr(m_SceneData->StaticViewMatrix));
    }

    void Renderer::PopulatePointLightUniforms() {
        if (!m_SceneData->Lights) {
            return;
        }

        if (!m_Uniforms->AllLights) {
            BufferLayout layout = LightingManager::c_LightDataLayout;

            BufferLayout pointLightLayout = PointLight::GetBufferLayout();
            for (int pointLightStepper = 0; pointLightStepper < MD_MAX_POINT_LIGHTS; ++pointLightStepper) {
                for (const BufferElement& element : pointLightLayout) {
                    layout.AddElement(element.Type, element.Name);
                }
            }

            BufferLayout directionLightLayout = DirectionalLight::GetBufferLayout();
            for (int dirLightStepper = 0; dirLightStepper < MD_MAX_DIR_LIGHTS; ++dirLightStepper) {
                for (const BufferElement& element : directionLightLayout) {
                    layout.AddElement(element.Type, element.Name);
                }
            }

            BufferLayout spotLightLayout = SpotLight::GetBufferLayout();
            for (int spotLightStepper = 0; spotLightStepper < MD_MAX_SPOT_LIGHTS; ++spotLightStepper) {
                for (const BufferElement& element : spotLightLayout) {
                    layout.AddElement(element.Type, element.Name);
                }
            }
            layout.CalculateOffsetsAndStride();
            m_Uniforms->AllLights = UniformBuffer::Create(layout.GetStride(), nullptr, c_PointLightDataBindingBlock);
            m_Uniforms->AllLights->SetLayout(layout);
        }

        m_Uniforms->AllLights->Bind();

        uint32_t pointLightCount;
        uint32_t dirLightCount;
        uint32_t spotLightCount;
        float paddingData = 0.0f;

        uint32_t elementIndex = 0;
        m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(m_SceneData->Lights->AmbientColor));
        m_Uniforms->AllLights->SetSubData(elementIndex++, &(m_SceneData->Lights->AmbientStrength));

        pointLightCount = static_cast<uint32_t>(m_SceneData->Lights->GetPointLights().size());
        m_Uniforms->AllLights->SetSubData(elementIndex++, &pointLightCount);
        dirLightCount = static_cast<uint32_t>(m_SceneData->Lights->GetDirectionalLights().size());
        m_Uniforms->AllLights->SetSubData(elementIndex++, &dirLightCount);
        spotLightCount = static_cast<uint32_t>(0);
        m_Uniforms->AllLights->SetSubData(elementIndex++, &spotLightCount);

        m_Uniforms->AllLights->SetSubData(elementIndex++, &paddingData);

        glm::vec3 defaultVec = glm::vec3(0.0f);

        for (uint32_t pointLightStepper = 0; pointLightStepper < MD_MAX_POINT_LIGHTS; ++pointLightStepper) {
            if (pointLightStepper < pointLightCount) {
                m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(m_SceneData->Lights->GetPointLights().at(pointLightStepper)->Color));
                m_Uniforms->AllLights->SetSubData(elementIndex++, &(m_SceneData->Lights->GetPointLights().at(pointLightStepper)->LinearAttenuation));

                m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(m_SceneData->Lights->GetPointLights().at(pointLightStepper)->Position));
                m_Uniforms->AllLights->SetSubData(elementIndex++, &(m_SceneData->Lights->GetPointLights().at(pointLightStepper)->QuadraticAttenuation));
            } else {
                m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(defaultVec));
                m_Uniforms->AllLights->SetSubData(elementIndex++, &paddingData);

                m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(defaultVec));
                m_Uniforms->AllLights->SetSubData(elementIndex++, &paddingData);
            }
        }

        for (uint32_t dirLightStepper = 0; dirLightStepper < MD_MAX_DIR_LIGHTS; ++dirLightStepper) {
            if (dirLightStepper < dirLightCount) {
                m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(m_SceneData->Lights->GetDirectionalLights().at(dirLightStepper)->Color));
                m_Uniforms->AllLights->SetSubData(elementIndex++, &(paddingData));

                m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(m_SceneData->Lights->GetDirectionalLights().at(dirLightStepper)->Direction));
                m_Uniforms->AllLights->SetSubData(elementIndex++, &(paddingData));
            }
            else {
                m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(defaultVec));
                m_Uniforms->AllLights->SetSubData(elementIndex++, &paddingData);

                m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(defaultVec));
                m_Uniforms->AllLights->SetSubData(elementIndex++, &paddingData);
            }
        }

        for (int spotLightStepper = 0; spotLightStepper < MD_MAX_SPOT_LIGHTS; ++spotLightStepper) {
            m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(defaultVec));
            m_Uniforms->AllLights->SetSubData(elementIndex++, &paddingData);

            m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(defaultVec));
            m_Uniforms->AllLights->SetSubData(elementIndex++, &paddingData);

            m_Uniforms->AllLights->SetSubData(elementIndex++, glm::value_ptr(defaultVec));
            m_Uniforms->AllLights->SetSubData(elementIndex++, &paddingData);
        }
    }

}
