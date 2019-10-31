// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: VertexArray.cpp
// Date: 30/10/2019

#include "mdpch.h"
#include "VertexArray.h"
#include "midori/renderer/Renderer.h"
#include "platform/opengl/OpenGLVertexArray.h"

namespace midori {

    VertexArray* VertexArray::Create() {
        switch (Renderer::GetAPI()) {
        case RendererAPI::OpenGL:;
            return new OpenGLVertexArray();
        case RendererAPI::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unsupported Rendering API has been selected");
        return nullptr;
    }

}
