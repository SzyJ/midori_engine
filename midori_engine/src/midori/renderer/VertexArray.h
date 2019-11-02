// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: VertexArray.h
// Date: 30/10/2019

#pragma once

#include <vector>
#include "midori/renderer/Buffer.h"

namespace midori {

    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const ref<IndexBuffer>& IndexBuffer) = 0;

        virtual const std::vector<ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const ref<IndexBuffer>& GetIndexBuffer() const = 0;

        static ref<VertexArray> Create();
    };

}
