// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLRenderer.cpp
// Date: 29/10/2019

#include "mdpch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace midori {


    ///////////////////
    // Vertex Buffer //
    ///////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
        : m_Size(size) {
        glCreateBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    }

    void OpenGLVertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    const BufferLayout& OpenGLVertexBuffer::GetLayout() const { return m_Layout; }

    void OpenGLVertexBuffer::SetLayout(const BufferLayout& bufferLayout) { m_Layout = bufferLayout; }


    //////////////////
    // Index Buffer //
    //////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
        : m_Count(count) {
        glCreateBuffers(1, &m_IndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_IndexBufferID);
    }

    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
    }

    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


    ////////////////////
    // Uniform Buffer //
    ////////////////////

    OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t bytesToAssign, void* data, uint32_t bindingBlock)
        : m_Size(bytesToAssign) {

        glGenBuffers(1, &m_UniformBufferID);
        glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID);
        if (data) {
            glBufferData(GL_UNIFORM_BUFFER, bytesToAssign, data, GL_STATIC_DRAW);
        } else {
            glBufferData(GL_UNIFORM_BUFFER, bytesToAssign, NULL, GL_STATIC_DRAW);
        }

        glBindBufferBase(GL_UNIFORM_BUFFER, bindingBlock, m_UniformBufferID);
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer() {
        glDeleteBuffers(1, &m_UniformBufferID);
    }

    void OpenGLUniformBuffer::Bind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID);
    }

    void OpenGLUniformBuffer::Unbind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void OpenGLUniformBuffer::SetData(void* newData) {
        glBufferData(GL_UNIFORM_BUFFER, m_Size, newData, GL_STATIC_DRAW);
    }

    void OpenGLUniformBuffer::SetSubData(uint32_t index, void* newData) {
        glBufferSubData(GL_UNIFORM_BUFFER, m_Layout.GetIndexOffset(index), m_Layout.GetIndexSize(index), newData);
    }


    //////////////////
    // Frame Buffer //
    //////////////////

    OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t frameWidth, uint32_t frameHeight) {
        // Make buffer
        glGenFramebuffers(1, &m_FrameBufferID);

        // Make Texture
        SetUpTexture(frameWidth, frameHeight);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer() {
        glDeleteFramebuffers(1, &m_FrameBufferID);
        glDeleteTextures(1, &m_TextureID);
    }

    void OpenGLFrameBuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
    }

    void OpenGLFrameBuffer::Unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::UpdateFrameSize(uint32_t width, uint32_t height) {
        glDeleteTextures(1, &m_TextureID);
        SetUpTexture(width, height);
    }

    // TODO: Allow for other options rather than just depth
    void OpenGLFrameBuffer::SetUpTexture(uint32_t width, uint32_t height) {
        // TODO: Move this to a texture class
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

}
