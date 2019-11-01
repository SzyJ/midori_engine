// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLShader.h
// Date: 01/11/2019

#pragma once

#include "midori/renderer/Shader.h"

#include <glm/mat4x4.hpp>

namespace midori {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader() = delete;
        OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc);
        ~OpenGLShader();

        void Bind() override;
        void Unbind() override;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

    private:
        uint32_t m_RendererID = 0;

        static inline bool CompileShader(const uint32_t shaderID, std::string& shaderSrc);
        static inline bool LinkProgram(const uint32_t programID);
    };

}
