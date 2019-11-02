// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: VertexArray.cpp
// Date: 02/11/2019

#include "mdpch.h"
#include "VertexArray.h"

#include "midori/renderer/Renderer.h"
#include "platform/opengl/OpenGLVertexArray.h"

namespace midori {

    ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unsupported Rendering API has been selected");
        return nullptr;
    }

}
