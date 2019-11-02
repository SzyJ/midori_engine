// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLVertexArray.h
// Date: 31/10/2019

#pragma once
#include "midori/renderer/VertexArray.h"

namespace midori {

    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const ref<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const ref<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<ref<VertexBuffer>>& GetVertexBuffers() const override;
        virtual const ref<IndexBuffer>& GetIndexBuffer() const override;
    private:
        uint32_t m_VertexArrayID;
        std::vector<ref<VertexBuffer>> m_VertexBuffers;
        ref<IndexBuffer> m_IndexBuffer;
    };

}
