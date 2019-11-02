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

#define MD_FILEPATH_MAX 255

#ifndef MD_VERT_EXT
#define MD_VERT_EXT "_Vert.glsl"
#endif

#ifndef MD_TESS_EXT
#define MD_TESS_EXT "_Tess.glsl"
#endif

#ifndef MD_GEOM_EXT
#define MD_GEOM_EXT "_Geom.glsl"
#endif

#ifndef MD_FRAG_EXT
#define MD_FRAG_EXT "_Frag.glsl"
#endif

namespace midori {

    Ref<Shader> Shader::Create(std::string& vertexSrc, std::string& fragmentSrc) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
        case RendererAPI::API::None:
        default:
            break;
        }

        MD_CORE_ERROR("An unsupported Rendering API has been selected");
        return nullptr;
    }

    Ref<Shader> Shader::Load(const std::string& shaderPath) {
        std::string vertexShaderSrc;
        std::string fragmentShaderSrc;
        //TODO: Add geom and tess shaders
        //std::string tesselationShaderSrc;
        //std::string geometryShaderSrc;

        char thisPath[MD_FILEPATH_MAX];
        std::strcpy(thisPath, shaderPath.c_str());
        char* const extPtr = thisPath + shaderPath.length();

        strcpy(extPtr, MD_VERT_EXT);
        GetSource(thisPath, vertexShaderSrc);

        strcpy(extPtr, MD_FRAG_EXT);
        GetSource(thisPath, fragmentShaderSrc);

        return Create(vertexShaderSrc, fragmentShaderSrc);
    }

    inline bool Shader::GetSource(const char* pathFrom, std::string& to) {
        const bool loadSuccess = LoadFile(pathFrom, to);
        if (!loadSuccess) {
            MD_CORE_WARN("Failed to open shader source: {0}", pathFrom);
        }

        return loadSuccess;
    }


}
