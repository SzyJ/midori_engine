// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Skybox.cpp
// Date: 11/11/2019

#include "mdpch.h"
#include "Skybox.h"

#include "midori/renderer/Renderer.h"

#define MD_CUBEMAP_TEXTURE_SLOT 30

namespace midori {

    inline float c_SkyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    Skybox::Skybox(const std::string& texturePath) {
        m_VertexArray = VertexArray::Create();

        ref<VertexBuffer> vb = VertexBuffer::Create(c_SkyboxVertices, 6 * 6 * 3);
        vb->SetLayout({ {ShaderDataType::Float3, "a_Position" } });
        m_VertexArray->AddVertexBuffer(vb);

        m_CubeMap = TextureCubeMap::Create(texturePath);
        m_CubeMap->Bind(MD_CUBEMAP_TEXTURE_SLOT);

        m_Shader = Shader::Load(MD_DEFAULT_RESOURCES"shaders/Skybox");
        m_Shader->Bind();
        m_Shader->UploadUniformInt("u_CubeMapTexture", MD_CUBEMAP_TEXTURE_SLOT);
    }

    Skybox::~Skybox() { }

    ref<Skybox> Skybox::Create(const std::string& texturePath) {
        return make_ref<Skybox>(texturePath);
    }

    void Skybox::Draw() {
        RenderCommand::SetDepthMask(false);

        Renderer::Submit(m_Shader, m_VertexArray);

        RenderCommand::SetDepthMask(true);
    }

}
