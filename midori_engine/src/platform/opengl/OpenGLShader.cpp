// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLShader.cpp
// Date: 01/11/2019

#include "mdpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace midori {

    OpenGLShader::OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc) {
        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        bool vertexCompiled = CompileShader(vertexShaderID, vertexSrc);
        bool fragmentCompiled = CompileShader(fragmentShaderID, fragmentSrc);

        if (!vertexCompiled || !fragmentCompiled) {
            return;
        }

        m_ShaderID = glCreateProgram();
        GLint program = m_ShaderID;

        glAttachShader(program, vertexShaderID);
        glAttachShader(program, fragmentShaderID);

        bool programLinked = LinkProgram(program);
        if (!programLinked) {
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);
            glDeleteProgram(program);
        }

        glDetachShader(program, vertexShaderID);
        glDetachShader(program, fragmentShaderID);
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

    void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }


    bool OpenGLShader::CompileShader(const GLuint shaderID, std::string& shaderSrc) {
        GLint compileSuccess;

        const GLchar* shaderGLSrc = shaderSrc.c_str();
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
}
