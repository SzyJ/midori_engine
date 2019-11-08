// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Shader.cpp
// Date: 08/11/2019

#include "mdpch.h"
#include "Shader.h"

#include "midori/core/tools/FileLoader.h"
#include "midori/renderer/Renderer.h"
#include "platform/opengl/OpenGLShader.h"

#define MD_FILEPATH_MAX 255

#ifndef MD_VERT_EXT
#define MD_VERT_EXT "_Vert.glsl"
#endif

#ifndef MD_TESSC_EXT
#define MD_TESSC_EXT "_Tess_C.glsl"
#endif

#ifndef MD_TESSE_EXT
#define MD_TESSE_EXT "_Tess_E.glsl"
#endif

#ifndef MD_GEOM_EXT
#define MD_GEOM_EXT "_Geom.glsl"
#endif

#ifndef MD_FRAG_EXT
#define MD_FRAG_EXT "_Frag.glsl"
#endif

namespace midori {

    ref<Shader> Shader::Create(std::string_view& vertexSrc, std::string_view& fragmentSrc, std::string_view& tessellationCtlSrc, std::string_view& tessellationEvaSrc, std::string_view& geometrySrc) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return make_ref<OpenGLShader>(vertexSrc, fragmentSrc, tessellationCtlSrc, tessellationEvaSrc, geometrySrc);
        case RendererAPI::API::None:
        default:
            break;
        }

        MD_CORE_ERROR("An unsupported Rendering API has been selected");
        return nullptr;
    }

    ref<Shader> Shader::Load(const std::string& shaderPath, const uint8_t shaderPrograms) {
        std::string vertexShaderSrc;
        std::string fragmentShaderSrc;
        std::string tessellationCtlShaderSrc;
        std::string tessellationEvaShaderSrc;
        std::string geometryShaderSrc;

        char thisPath[MD_FILEPATH_MAX];
        std::strcpy(thisPath, shaderPath.c_str());
        char* const extPtr = thisPath + shaderPath.length();

        if (shaderPrograms & (uint8_t) ShaderProgramType::vertex) {
            strcpy(extPtr, MD_VERT_EXT);
            GetSource(thisPath, vertexShaderSrc);
        }

        if (shaderPrograms & (uint8_t) ShaderProgramType::fragment) {
            strcpy(extPtr, MD_FRAG_EXT);
            GetSource(thisPath, fragmentShaderSrc);
        }

        if (shaderPrograms & (uint8_t) ShaderProgramType::tessellation) {
            strcpy(extPtr, MD_TESSC_EXT);
            GetSource(thisPath, tessellationCtlShaderSrc);
            strcpy(extPtr, MD_TESSE_EXT);
            GetSource(thisPath, tessellationEvaShaderSrc);
        }

        if (shaderPrograms & (uint8_t) ShaderProgramType::geometry) {
            strcpy(extPtr, MD_GEOM_EXT);
            GetSource(thisPath, geometryShaderSrc);
        }

        return Create(
            std::string_view(vertexShaderSrc.c_str()),
            std::string_view(fragmentShaderSrc.c_str()),
            std::string_view(tessellationCtlShaderSrc.c_str()),
            std::string_view(tessellationEvaShaderSrc.c_str()),
            std::string_view(geometryShaderSrc.c_str())
        );
    }

    inline bool Shader::GetSource(const char* pathFrom, std::string& to) {
        const bool loadSuccess = LoadFile(pathFrom, to);
        MD_CORE_ASSERT(loadSuccess, "Failed to open shader source: {0}", pathFrom);
        return loadSuccess;
    }


}
