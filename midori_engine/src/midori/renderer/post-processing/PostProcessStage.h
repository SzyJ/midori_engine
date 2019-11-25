// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PostProcessStage.h
// Date: 25/11/2019

#pragma once

#include "midori/core/Core.h"
#include "midori/renderer/Shader.h"
#include "midori/renderer/Buffer.h"

namespace midori {

    class PostProcessStage {
    public:
        PostProcessStage() = delete;
        PostProcessStage(const char* shaderPath) {
            m_Shader = Shader::Load(shaderPath);
        }

        ~PostProcessStage() = default;

        void Bind() {
            m_Shader->Bind();
            m_Shader->UploadUniformInt("u_InputTexture", m_InputTexture);
            m_Shader->UploadUniformFloat("u_TotalTime", m_TotalTime);
            m_Shader->UploadUniformInt("u_FrameWidth", m_Width);
            m_Shader->UploadUniformInt("u_FrameHeight", m_Height);

            m_OutputBuffer->Bind();
        }

        void BindTexture(uint32_t textureSlot) {
            m_OutputBuffer->BindTexture(textureSlot);
        }

        void Unbind() {
            m_Shader->Unbind();
            m_OutputBuffer->Unbind();
        }

        void SetInputTexture(uint32_t inputTexture) { m_InputTexture = inputTexture; }
        void SetTime(float time) { m_TotalTime = time; }

        void UpdateFrameSize(uint32_t width, uint32_t height) {
            m_Width = width;
            m_Height = height;

            if (!m_OutputBuffer) {
                m_OutputBuffer = FrameBufferColor2D::Create(width, height);
            } else {
                m_OutputBuffer->UpdateFrameSize(width, height);
            }
        }

    private:
        uint32_t m_Width, m_Height;

        float m_TotalTime;
        uint32_t m_InputTexture;
        ref<Shader> m_Shader;
        ref<FrameBufferColor2D> m_OutputBuffer;
    };

}
