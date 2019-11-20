// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLShader.cpp
// Date: 08/11/2019

#include "mdpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace midori {

    OpenGLShader::OpenGLShader(std::string_view& vertexSrc, std::string_view& fragmentSrc, std::string_view& tessellationCtlSrc, std::string_view& tessellationEvaSrc, std::string_view& geometrySrc) {
        m_ShaderID = glCreateProgram();
        GLint program = m_ShaderID;

        GLuint vertexShaderID = AddShader(program, vertexSrc, GL_VERTEX_SHADER);
        GLuint fragmentShaderID = AddShader(program, fragmentSrc, GL_FRAGMENT_SHADER);
        GLuint tessellationCtlShaderID = AddShader(program, tessellationCtlSrc, GL_TESS_CONTROL_SHADER);
        GLuint tessellationEvaShaderID = AddShader(program, tessellationEvaSrc, GL_TESS_EVALUATION_SHADER);
        GLuint geometryShaderID = AddShader(program, geometrySrc, GL_GEOMETRY_SHADER);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        glDeleteShader(tessellationCtlShaderID);
        glDeleteShader(tessellationEvaShaderID);
        glDeleteShader(geometryShaderID);

        bool programLinked = LinkProgram(program);
        if (!programLinked) {
            glDeleteProgram(program);
        } else {
            glDetachShader(program, vertexShaderID);
            glDetachShader(program, fragmentShaderID);
            glDetachShader(program, tessellationCtlShaderID);
            glDetachShader(program, tessellationEvaShaderID);
            glDetachShader(program, geometryShaderID);
        }
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_ShaderID);
    }

    void OpenGLShader::Bind() {
        glUseProgram(m_ShaderID);
    }

    void OpenGLShader::Unbind() {
        glUseProgram(0);
    }

    void OpenGLShader::BindUniformBuffer(const char* name, const uint32_t bindingBlock) {
        const uint32_t uniformBlockIndex = glGetUniformBlockIndex(m_ShaderID, name);
        glUniformBlockBinding(m_ShaderID, uniformBlockIndex, bindingBlock);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector) {
        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform3f(location, vector.x, vector.y, vector.z);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    bool OpenGLShader::CompileShader(const GLuint shaderID, std::string_view& shaderSrc) {
        GLint compileSuccess;

        const GLchar* shaderGLSrc = shaderSrc.data();
        glShaderSource(shaderID, 1, &shaderGLSrc, NULL);
        glCompileShader(shaderID);
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileSuccess);

        if (compileSuccess == GL_FALSE) {
            const int INFO_LOG_BUFFER_LENGTH = 512;
            GLchar infoLog[INFO_LOG_BUFFER_LENGTH];

            glGetShaderInfoLog(shaderID, INFO_LOG_BUFFER_LENGTH, NULL, infoLog);
            MD_CORE_WARN("Failed to compile shader: {0}", infoLog);
            glDeleteShader(shaderID);
            return false;
        }

        return true;
    }

    bool OpenGLShader::LinkProgram(const GLuint programID) {
        GLint linkSuccess;

        glLinkProgram(programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE) {
            const int INFO_LOG_BUFFER_LENGTH = 512;
            GLchar infoLog[INFO_LOG_BUFFER_LENGTH];

            std::strcpy(infoLog, "No info log available");

            glGetShaderInfoLog(programID, INFO_LOG_BUFFER_LENGTH, NULL, infoLog);
            MD_CORE_WARN("Failed to link shaders to program: {0}", infoLog);
            return false;
        }

        return true;
    }

    uint32_t OpenGLShader::AddShader(const uint32_t programID, std::string_view& shaderSrc, const uint32_t shaderType) {
        if (shaderSrc.empty()) {
            return 0;
        }

        uint32_t shaderID = glCreateShader(shaderType);
        bool compiled = CompileShader(shaderID, shaderSrc);

        if (!compiled) {
            glDeleteShader(shaderID);
            return 0;
        }

        glAttachShader(programID, shaderID);

        return shaderID;
    }
}
