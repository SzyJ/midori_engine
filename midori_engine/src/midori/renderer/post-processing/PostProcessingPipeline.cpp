// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PostProcessingPipeline.cpp
// Date: 25/11/2019

#include "mdpch.h"
#include "PostProcessingPipeline.h"
#include "midori/renderer/Renderer.h"

namespace midori {

    PostProcessingPipeline::PostProcessingPipeline() {
        float screenQuadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions     // texCoords
        -1.0f,  1.0f,    0.0f, 1.0f,
        -1.0f, -1.0f,    0.0f, 0.0f,
         1.0f, -1.0f,    1.0f, 0.0f,

        -1.0f,  1.0f,    0.0f, 1.0f,
         1.0f, -1.0f,    1.0f, 0.0f,
         1.0f,  1.0f,    1.0f, 1.0f
        };
        auto vertexBuffer = VertexBuffer::Create(screenQuadVertices, (2 + 2) * 3 * 2);
        vertexBuffer->SetLayout({
            {ShaderDataType::Float2, "a_Position"},
            {ShaderDataType::Float2, "a_TexCoord"}
        });
        m_ScreenQuad = VertexArray::Create();
        m_ScreenQuad->AddVertexBuffer(vertexBuffer);

        m_SimpleDrawShader = Shader::Load(MD_DEFAULT_RESOURCES"shaders/DrawPostProcessQuad");
    }

    void PostProcessingPipeline::BeginPostProcess() {
        m_InputFrame->Bind();
    }

    void PostProcessingPipeline::FinishPostProcess() {
        m_InputFrame->Unbind();
        m_InputFrame->BindTexture(MD_POST_PROCESS_TEX_OFFSET);

        uint32_t inputTextureSlot = MD_POST_PROCESS_TEX_OFFSET;
        for (PostProcessStage& stage : m_ProcessStages) {
            stage.SetInputTexture(inputTextureSlot);
            stage.Bind();

            DrawScreenQuad();

            stage.Unbind();
            stage.BindTexture(inputTextureSlot);
        }

        m_SimpleDrawShader->Bind();
        m_SimpleDrawShader->UploadUniformInt("u_InputTexture", inputTextureSlot);

        DrawScreenQuad();
        m_SimpleDrawShader->Unbind();
    }

    void PostProcessingPipeline::DrawScreenQuad() {
        RenderCommand::SetDepthTest(false);
        RenderCommand::Clear();

        m_ScreenQuad->Bind();
        RenderCommand::DrawVertices(m_ScreenQuad);
        RenderCommand::SetDepthTest(true);
    }

    void PostProcessingPipeline::UpdateScreenSize(uint32_t width, uint32_t height) {
        if (!m_InputFrame) {
            m_InputFrame = FrameBufferColor2D::Create(width, height);
        } else {
            m_InputFrame->UpdateFrameSize(width, height);
        }

        for (PostProcessStage& stage : m_ProcessStages) {
            stage.UpdateFrameSize(width, height);
        }
    }

}
