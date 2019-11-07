// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: MeshLoader.cpp
// Date: 07/11/2019

#include "mdpch.h"
#include "MeshLoader.h"

#include <tiny_obj_loader.h>

namespace midori {

    ref<VertexArray> MeshLoader::Load(const std::string& path) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn;
        std::string err;

        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), nullptr, true);

        if (!warn.empty()) {
            MD_CORE_WARN("Warning when loading obj: {0}", warn);
        }

        if (!err.empty()) {
            MD_CORE_ERROR("Failed to load obj: {0}", err);
        }

        if (!ret) {
            return nullptr;
        }


        BufferLayout bufferLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            {ShaderDataType::Float2, "a_TexCoord"}
        };

        std::vector<uint32_t> indexBuffer;
        std::vector<float> meshBufferData;

        ref<VertexArray> va = VertexArray::Create();

        uint32_t indexStepper = 0;

        for (tinyobj::shape_t shape : shapes) {
            size_t index_offset = 0;

            uint8_t vertexData = (uint8_t) MeshLoadedData::none;
            BufferLayout bufferLayout;

            for (unsigned int verticesInFace : shape.mesh.num_face_vertices) {
                for (size_t vertexIndex = 0; vertexIndex < verticesInFace; ++vertexIndex) {
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + vertexIndex];

                    if (!attrib.vertices.empty()) {
                        vertexData |= (uint8_t) MeshLoadedData::p;

                        meshBufferData.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
                        meshBufferData.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
                        meshBufferData.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
                    }

                    if (!attrib.normals.empty()) {
                        vertexData |= (uint8_t) MeshLoadedData::n;

                        meshBufferData.push_back(attrib.normals[3 * idx.normal_index + 0]);
                        meshBufferData.push_back(attrib.normals[3 * idx.normal_index + 1]);
                        meshBufferData.push_back(attrib.normals[3 * idx.normal_index + 2]);
                    }

                    if (!attrib.texcoords.empty()) {
                        vertexData |= (uint8_t) MeshLoadedData::t;

                        meshBufferData.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
                        meshBufferData.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
                    }
                    indexBuffer.push_back(indexStepper++);
                }
                index_offset += verticesInFace;
            }

            if (vertexData & (uint8_t) MeshLoadedData::p) {
                bufferLayout.AddElement(ShaderDataType::Float3, "a_Position");
            }
            if (vertexData & (uint8_t) MeshLoadedData::n) {
                bufferLayout.AddElement(ShaderDataType::Float3, "a_Normal");
            }
            if (vertexData & (uint8_t) MeshLoadedData::t) {
                bufferLayout.AddElement(ShaderDataType::Float2, "a_TexCoord");
            }
            bufferLayout.CalculateOffsetsAndStride();

            ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(meshBufferData.data(), meshBufferData.size());
            vertexBuffer->SetLayout(bufferLayout);
            va->AddVertexBuffer(vertexBuffer);
        }



        va->SetIndexBuffer(IndexBuffer::Create(indexBuffer.data(), indexBuffer.size()));

        return va;
    }

}
