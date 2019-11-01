// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Shader.cpp
// Date: 29/10/2019

#include "mdpch.h"
#include "Shader.h"

#include "midori/core/tools/FileLoader.h"
#include "midori/renderer/Renderer.h"
#include "platform/opengl/OpenGLShader.h"

namespace midori {

    Shader* Shader::Create(std::string& vertexSrc, std::string& fragmentSrc) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:;
            return new OpenGLShader(vertexSrc, fragmentSrc);
        case RendererAPI::API::None:
        default:
            break;
        }

        MD_CORE_ERROR("An unsupported Rendering API has been selected");
        return nullptr;
    }

    Shader* Shader::Load(const char* vertShaderPath, const char* fragShaderPath) {
        std::string vertexShaderSrc;
        bool vertSuccess = LoadFile(vertShaderPath, vertexShaderSrc);
        if (!vertSuccess) {
            MD_CORE_ERROR("Failed to load Vertex source code: {0}", vertShaderPath);
            return nullptr;
        }

        std::string fragmentShaderSrc;
        bool fragSuccess = LoadFile(fragShaderPath, fragmentShaderSrc);
        if (!fragSuccess) {
            MD_CORE_ERROR("Failed to load Frag source code: {0}", fragmentShaderSrc);
            return nullptr;
        }

        return Create(vertexShaderSrc, fragmentShaderSrc);
    }

}
