// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Buffer.h
// Date: 29/10/2019

#pragma once

#include "midori/core/Log.h"

namespace midori {

    enum class ShaderDataType {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,  
        Int,
        Int2,
        Int3,
        Int4,
        Bool,
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float:  return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::Mat3:   return 4 * 3 * 3;
        case ShaderDataType::Mat4:   return 4 * 4 * 4;
        case ShaderDataType::Int:    return 4;
        case ShaderDataType::Int2:   return 4 * 2;
        case ShaderDataType::Int3:   return 4 * 3;
        case ShaderDataType::Int4:   return 4 * 4;
        case ShaderDataType::Bool:   return 1;
        }

        MD_CORE_WARN("Unknown ShaderDataType");
        return 0;
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint64_t Offset;
        bool Normalized;

        BufferElement() = default;
        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

        uint32_t GetComponentCount() const {
            switch (Type) {
            case ShaderDataType::Float:  return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Mat3:   return 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4;
            case ShaderDataType::Int:    return 1;
            case ShaderDataType::Int2:   return 2;
            case ShaderDataType::Int3:   return 3;
            case ShaderDataType::Int4:   return 4;
            case ShaderDataType::Bool:   return 1;
            }

            MD_CORE_WARN("Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_Elements(elements) {
            CalculateOffsetsAndStride();
        }

        inline uint32_t GetStride() const { return m_Stride; }
        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        inline void AddElement(ShaderDataType type, const std::string& name, bool normalized = false) { m_Elements.emplace_back(type, name, normalized); }
        inline const uint64_t GetIndexOffset(uint32_t index) const { return m_Elements.at(index).Offset; }
        inline const uint32_t GetIndexSize(uint32_t index) const { return m_Elements.at(index).Size; }

        void CalculateOffsetsAndStride() {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& bufferLayout) = 0;

        virtual uint32_t GetSize() const = 0;

        static ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };

    class UniformBuffer {
    public:
        virtual ~UniformBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& bufferLayout) = 0;

        virtual void SetData(void* newData) = 0;
        virtual void SetSubData(uint32_t index, void* newData) = 0;

        virtual uint32_t GetSize() const = 0;

        static ref<UniformBuffer> Create(uint32_t bytesToAssign, void* data, uint32_t bindingBlock = 0);
    };

    class FrameBufferDepth2D {
    public:
        virtual ~FrameBufferDepth2D() = default;

        virtual void Bind(uint8_t textureSlot) const = 0;
        virtual void Unbind() const = 0;

        virtual void UpdateFrameSize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetDepthTextureID() = 0;

        static ref<FrameBufferDepth2D> Create(uint32_t frameWidth, uint32_t frameHeight);
    };

    class FrameBufferColor2D {
    public:
        virtual ~FrameBufferColor2D() = default;

        virtual void Bind() const = 0;
        virtual void BindTexture(uint8_t textureSlot) const = 0;

        virtual void Unbind() const = 0;

        virtual void UpdateFrameSize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetDepthTextureID() = 0;

        static ref<FrameBufferColor2D> Create(uint32_t frameWidth, uint32_t frameHeight);
    };

    class FrameBufferColorCube {
    public:
        virtual ~FrameBufferColorCube() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void UpdateFrameSize(uint32_t size) = 0;

        static ref<FrameBufferColorCube> Create(uint32_t size);
    };

}
