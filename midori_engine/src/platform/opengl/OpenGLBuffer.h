// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLRenderer.h
// Date: 29/10/2019

#pragma once
#include "midori/renderer/Buffer.h"

namespace midori {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t m_VertexBufferID;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const { return m_Count; }

    private:
        uint32_t m_IndexBufferID, m_Count;
    };

}
