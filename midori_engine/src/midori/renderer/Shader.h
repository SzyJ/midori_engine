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
        virtual ~Shader() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void UploadUniformInt(const std::string& name, int value) = 0;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

        static ref<Shader> Create(std::string& vertexSrc, std::string& fragmentSrc);
        static ref<Shader> Load(const std::string& shaderPath);

    private:
        static inline bool GetSource(const char* pathFrom, std::string& to);

    };

}
