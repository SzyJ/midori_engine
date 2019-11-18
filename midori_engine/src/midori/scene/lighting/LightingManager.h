// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Header.h
// Date: 13/11/2019

#pragma once

#include "midori/scene/lighting/Lights.h"
#include "midori/renderer/Buffer.h"

#include <vector>

namespace midori {

    class LightingManager {
    public:
        static inline const BufferLayout c_LightDataLayout = BufferLayout({
            {ShaderDataType::Float3, "AmbientColor"},
            {ShaderDataType::Float, "AmbientStrength"},

            {ShaderDataType::Int, "PointLightCount"},
            {ShaderDataType::Int, "DirectionalLightCount"},
            {ShaderDataType::Int, "SpotLightCount"},
            {ShaderDataType::Float, "Padding0"}
        });
        glm::vec3 AmbientColor = glm::vec3(1.0f, 1.0f, 1.0f);
        float AmbientStrength = 0.5f;

        LightingManager() = default;
        ~LightingManager() = default;

        void AddPointLight(const ref<PointLight>& newLight) { m_PointLights.push_back(newLight); }
        const std::vector<ref<PointLight>>& GetPointLights() { return m_PointLights; }

        void AddDirectionalLight(const ref<DirectionalLight>& newLight) { m_DirectionalLight.push_back(newLight); }
        const std::vector<ref<DirectionalLight>>& GetDirectionalLights() { return m_DirectionalLight; }

    private:


        std::vector<ref<PointLight>> m_PointLights;
        std::vector<ref<DirectionalLight>> m_DirectionalLight;
    };

}
