// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Buffer.cpp
// Date: 29/10/2019

#include "mdpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLBuffer.h"

namespace midori {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:;
            return new OpenGLVertexBuffer(vertices, size);
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unsupported Rendering API has been selected");
        return nullptr;
    }


    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:;
            return new OpenGLIndexBuffer(indices, count);
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unspported Rendering API has been selected");
        return nullptr;
    }

}
