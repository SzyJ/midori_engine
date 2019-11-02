// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Texture.cpp
// Date: 03/10/2019

#include "mdpch.h"
#include "Texture.h"

#include "midori/renderer/Renderer.h"
#include "platform/opengl/OpenGLTexture.h"

namespace midori {

    ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:;
            return std::make_shared<OpenGLTexture2D>(path);
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unsupported Rendering API has been selected");
        return nullptr;
    }

}
