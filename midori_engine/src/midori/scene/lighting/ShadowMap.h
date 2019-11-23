// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: ShadowMap.h
// Date: 20/11/2019

#pragma once

#include "midori/core/Core.h"
#include "midori/renderer/Buffer.h"
#include "midori/renderer/Shader.h"
#include "midori/renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

#define MD_DEF_SHADOW_MAP_PERS_NEAR_Z 1.0f
#define MD_DEF_SHADOW_MAP_PERS_FAR_Z 25.0f

#define MD_DEF_SHADOW_MAP_ORTH_NEAR_Z 10.0f
#define MD_DEF_SHADOW_MAP_ORTH_FAR_Z 25.0f

#define MD_DEPTH_MAP_SHADER MD_DEFAULT_RESOURCES"shaders/DirectionalLightShadowMap"

namespace midori {

    class ShadowMap {
    public:
        static ref<Shader> GetShader() {
            if (!s_Initialized) {
                s_DepthMapShader = Shader::Load(MD_DEPTH_MAP_SHADER);
                s_Initialized = true;
            }
            return s_DepthMapShader;
        }
    private:
        static inline ref<Shader> s_DepthMapShader;
        static inline bool s_Initialized = false;
    };

    class DirectionalLightShadowMap {
    public:
        float OrthoNearZ = 10.0f;
        float OrthoFarZ = 25.0f;
        float OrthoDistFromOrigin = 15.0f;
        float OrthoSize = 25.0f;

        float PersNearZ = 1.0f;
        float PersFarZ = 25.0f;
        float PersFOV = 45.0f;


        DirectionalLightShadowMap() = default;
        DirectionalLightShadowMap(uint32_t width, uint32_t height) {
            m_DepthMap = FrameBufferDepth2D::Create(width, height);
            m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
            m_Initialized = true;
        }
        ~DirectionalLightShadowMap() = default;

        void SetFrameSize(uint32_t width, uint32_t height) {

            if (!m_DepthMap) {
                m_DepthMap = FrameBufferDepth2D::Create(width, height);
            } else {
                m_DepthMap->UpdateFrameSize(width, height);
            }
            m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
            m_Initialized = true;
        }

        void BeginShadowMapPerspectiveScene(uint8_t index, glm::vec3 position, glm::vec3 direction) {
            m_DepthMap->Bind(10 + index);

            ShadowMap::GetShader()->Bind();
            ShadowMap::GetShader()->UploadUniformMat4("u_LightViewProjection", GetPerspectiveViewProjection(position, direction));

            RenderCommand::Clear();
        }

        void BeginShadowMapOrthoScene(uint8_t index, glm::vec3 direction) {
            m_DepthMap->Bind(20 + index);

            ShadowMap::GetShader()->Bind();
            ShadowMap::GetShader()->UploadUniformMat4("u_LightViewProjection", GetOrthographicViewProjection(direction));

            RenderCommand::Clear();
        }

        void EndShadowMapScene() {
            ShadowMap::GetShader()->Unbind();
            m_DepthMap->Unbind();
        }

        bool IsInitialized() { return m_Initialized; }

        uint32_t GetDepthTextureID() { return m_DepthMap->GetDepthTextureID(); }

        glm::mat4 GetPerspectiveViewProjection(glm::vec3 position, glm::vec3 direction) {
            glm::mat4 lightProjection = glm::perspective(glm::radians(PersFOV), m_AspectRatio, PersNearZ, PersFarZ);
            glm::mat4 lightView = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));

            return lightProjection * lightView;
        }

        glm::mat4 GetOrthographicViewProjection(glm::vec3 direction) {
            glm::mat4 lightProjection = glm::ortho(-OrthoSize, OrthoSize, -OrthoSize, OrthoSize, OrthoNearZ, OrthoFarZ);
            glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f) - (direction * OrthoDistFromOrigin), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));

            return lightProjection * lightView;
        }
        
    private:
        float m_AspectRatio;
        bool m_Initialized = false;
        ref<FrameBufferDepth2D> m_DepthMap;
    };

}
