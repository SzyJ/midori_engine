// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Shader.h
// Date: 29/10/2019

#pragma once
#include <string>
#include <glm/glm.hpp>

namespace midori {

    enum class ShaderProgramType : uint8_t {
        none = 0,
        vertex = BIT(1),
        fragment = BIT(2),
        tessellation = BIT(3),
        geometry = BIT(4),
        other = BIT(5)
    };
    
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void BindUniformBuffer(const char* name, uint32_t bindingBlock) = 0;

        virtual void UploadUniformInt(const std::string& name, int value) = 0;

        virtual void UploadUniformFloat(const std::string& name, float value) = 0;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) = 0;

        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

        static ref<Shader> Create(
            std::string_view& vertexSrc,
            std::string_view& fragmentSrc = std::string_view(),
            std::string_view& tessellationCtlSrc = std::string_view(),
            std::string_view& tessellationEvaSrc = std::string_view(),
            std::string_view& geometrySrc = std::string_view()
        );
        static ref<Shader> Load(const std::string& shaderPath, const uint8_t shaderPrograms = ((uint8_t)ShaderProgramType::vertex | (uint8_t)ShaderProgramType::fragment));

    private:
        static inline bool GetSource(const char* pathFrom, std::string& to);

    };

}
