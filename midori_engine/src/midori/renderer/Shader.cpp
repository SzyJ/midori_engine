// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Shader.cpp
// Date: 29/10/2019

#include "mdpch.h"
#include "Shader.h"
#include <glad/glad.h>


namespace midori {

    Shader::Shader(std::string& vertexSrc, std::string& fragmentSrc) {
        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        bool vertexCompiled = CompileShader(vertexShaderID, vertexSrc);
        bool fragmentCompiled = CompileShader(fragmentShaderID, fragmentSrc);

        if (!vertexCompiled || !fragmentCompiled) {
            return;
        }

        m_RendererID = glCreateProgram();
        GLint program = m_RendererID;

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

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    bool Shader::CompileShader(const GLuint shaderID, std::string& shaderSrc) {
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

    bool Shader::LinkProgram(const GLuint programID) {
        GLint linkSuccess;

        glLinkProgram(programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE) {
            const int INFO_LOG_BUFFER_LENGTH = 512;
            GLchar infoLog[INFO_LOG_BUFFER_LENGTH];

            glGetShaderInfoLog(programID, INFO_LOG_BUFFER_LENGTH, NULL, infoLog);
            MD_CORE_WARN("Failed to link shaders to program: {0}", infoLog);
            return false;
        }

        return true;
    }

}
