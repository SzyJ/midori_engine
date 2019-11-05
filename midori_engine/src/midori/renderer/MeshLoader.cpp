// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: MeshLoader.cpp
// Date: 05/11/2019

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

        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), 0, true);

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
            {ShaderDataType::Float3, "a_Normal"}//,
            //{ShaderDataType::Float2, "a_TexCoord"}
        };

        std::vector<uint32_t> indexBuffer;
        std::vector<float> meshBufferData;

        ref<VertexArray> va = VertexArray::Create();
        uint32_t indexStepper = 0;

        for (size_t s = 0; s < shapes.size(); s++) {
            tinyobj::shape_t shape = shapes[s];

            size_t index_offset = 0;

            for (unsigned int verticesInFace : shape.mesh.num_face_vertices) {

                for (size_t vertexIndex = 0; vertexIndex < verticesInFace; ++vertexIndex) {
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + vertexIndex];

                    tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
                    tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
                    tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
                    tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
                    //tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                    //tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];

                    meshBufferData.push_back(vx);
                    meshBufferData.push_back(vy);
                    meshBufferData.push_back(vz);
                    meshBufferData.push_back(nx);
                    meshBufferData.push_back(ny);
                    meshBufferData.push_back(nz);
                    //meshBufferData.push_back(tx);
                    //meshBufferData.push_back(ty);

                    //indexBuffer.push_back(idx.vertex_index);
                    indexBuffer.push_back(indexStepper++);
                }
                index_offset += verticesInFace;

                //for (uint32_t i = 0; i < verticesInFace; ++i) {
                //    indexBuffer.push_back(index_offset - (verticesInFace - 1 - i));
                //}

            }

            
        }
        ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(meshBufferData.data(), meshBufferData.size());
        vertexBuffer->SetLayout(bufferLayout);
        va->AddVertexBuffer(vertexBuffer);
        va->SetIndexBuffer(IndexBuffer::Create(indexBuffer.data(), indexBuffer.size()));

        return va;
    }

}
