// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Shader.h
// Date: 29/10/2019

#pragma once
#include <string>
#include <glm/glm.hpp>

namespace midori {

    class Shader {
    public:
        Shader() = delete;
        Shader(std::string& vertexSrc, std::string& fragmentSrc);
        ~Shader();

        void Bind();
        void Unbind();

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        uint32_t m_RendererID = 0;

        static inline bool CompileShader(const uint32_t shaderID, std::string& shaderSrc);
        static inline bool LinkProgram(const uint32_t programID);
    };

}
