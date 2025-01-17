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

        virtual const BufferLayout& GetLayout() const override;
        virtual void SetLayout(const BufferLayout& bufferLayout) override;

        virtual uint32_t GetSize() const override { return m_Size; }

    private:
        uint32_t m_VertexBufferID, m_Size;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_IndexBufferID, m_Count;
    };

    class OpenGLUniformBuffer : public UniformBuffer {
    public:
        OpenGLUniformBuffer(uint32_t bytesToAssign, void* data, uint32_t bindingBlock);
        ~OpenGLUniformBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const BufferLayout& GetLayout() const override { return m_Layout; }
        virtual void SetLayout(const BufferLayout& bufferLayout) override { m_Layout = bufferLayout; }
      
        virtual void SetData(void* newData) override;
        virtual void SetSubData(uint32_t index, void* newData) override;

        virtual uint32_t GetSize() const override { return m_Size; }

    private:
        uint32_t m_UniformBufferID, m_Size;
        BufferLayout m_Layout;
    };

    class OpenGLFrameBufferDepth2D : public FrameBufferDepth2D {
    public:
        OpenGLFrameBufferDepth2D(uint32_t frameWidth, uint32_t frameHeight);
        ~OpenGLFrameBufferDepth2D();

        virtual void Bind(uint8_t textureSlot) const override;
        virtual void Unbind() const override;

        virtual void UpdateFrameSize(uint32_t width, uint32_t height) override;

        virtual uint32_t GetDepthTextureID() override { return m_TextureID; }

    private:
        uint32_t m_FrameBufferID, m_TextureID;

        inline void SetUpTexture(uint32_t width, uint32_t height);
    };

    class OpenGLFrameBufferColor2D : public FrameBufferColor2D {
    public:
        OpenGLFrameBufferColor2D(uint32_t frameWidth, uint32_t frameHeight);
        ~OpenGLFrameBufferColor2D();

        virtual void Bind() const override;
        virtual void BindTexture(uint8_t textureSlot) const override;
        virtual void Unbind() const override;

        virtual void UpdateFrameSize(uint32_t width, uint32_t height) override;

        virtual uint32_t GetDepthTextureID() override { return m_TextureID; }

    private:
        uint32_t m_FrameBufferID, m_TextureID, m_RenderBufferID;

        inline void SetUpTexture(uint32_t width, uint32_t height);
        inline void SetUpRenderBuffer(uint32_t width, uint32_t height);
    };

    class OpenGLFrameBufferColorCube : public FrameBufferColorCube {
    public:
        OpenGLFrameBufferColorCube(uint32_t size);
        ~OpenGLFrameBufferColorCube();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void UpdateFrameSize(uint32_t size) override;
    };

}
