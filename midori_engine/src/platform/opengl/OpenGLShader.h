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
        OpenGLShader(std::string_view& vertexSrc, std::string_view& fragmentSrc, std::string_view& tessellationCtlSrc, std::string_view& tessellationEvaSrc, std::string_view& geometrySrc);
        ~OpenGLShader();

        void Bind() override;
        void Unbind() override;

        void UploadUniformInt(const std::string& name, int value) override;

        void UploadUniformFloat(const std::string& name, float value) override;
        void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) override;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

    private:

        uint32_t m_ShaderID = 0;

        static inline bool CompileShader(const uint32_t shaderID, std::string_view& shaderSrc);
        static inline bool LinkProgram(const uint32_t programID);
        static inline uint32_t AddShader(const uint32_t programID, std::string_view& shaderSrc, const uint32_t shaderType);
    };

}
