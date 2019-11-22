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

    ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return make_ref<OpenGLVertexBuffer>(vertices, size);
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unsupported Rendering API has been selected");
        return nullptr;
    }

    ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return make_ref<OpenGLIndexBuffer>(indices, count);
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unspported Rendering API has been selected");
        return nullptr;
    }

    ref<UniformBuffer> UniformBuffer::Create(uint32_t bytesToAssign, void* data, uint32_t bindingBlock) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return make_ref<OpenGLUniformBuffer>(bytesToAssign, data, bindingBlock);
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unspported Rendering API has been selected");
        return nullptr;
    }

    ref<FrameBufferDepth2D> FrameBufferDepth2D::Create(uint32_t frameWidth, uint32_t frameHeight) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return make_ref<OpenGLFrameBufferDepth2D>(frameWidth, frameHeight);
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unspported Rendering API has been selected");
        return nullptr;
    }

    ref<FrameBufferColorCube> FrameBufferColorCube::Create(uint32_t size) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return make_ref<OpenGLFrameBufferColorCube>(size);
        case RendererAPI::API::None:
        default:
            break;
        }
        MD_CORE_ERROR("An unspported Rendering API has been selected");
        return nullptr;
    }

}
