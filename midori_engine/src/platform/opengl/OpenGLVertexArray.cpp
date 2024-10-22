// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLVertexArray.cpp
// Date: 31/10/2019

#include "mdpch.h"
#include "OpenGLVertexArray.h"
#include "platform/opengl/OpenGLBuffer.h"

#include <glad/glad.h>

namespace midori {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float:  return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3:   return GL_FLOAT;
        case ShaderDataType::Mat4:   return GL_FLOAT;
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Int2:   return GL_INT;
        case ShaderDataType::Int3:   return GL_INT;
        case ShaderDataType::Int4:   return GL_INT;
        case ShaderDataType::Bool:   return GL_BOOL;
        }

        MD_CORE_WARN("Unknown ShaderDataType");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &m_VertexArrayID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_VertexArrayID);
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(m_VertexArrayID);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const ref<VertexBuffer>& vertexBuffer) {

        MD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Buffer Layout not set in Vertex Buffer");
        glBindVertexArray(m_VertexArrayID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();

        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                reinterpret_cast<const GLvoid*>(element.Offset)
            );
            ++index;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const ref<IndexBuffer>& indexBuffer) {
        glBindVertexArray(m_VertexArrayID);

        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

    const std::vector<ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const { return m_VertexBuffers; }

    const ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const { return m_IndexBuffer; }

}
