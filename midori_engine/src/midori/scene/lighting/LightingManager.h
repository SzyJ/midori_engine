// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Header.h
// Date: 13/11/2019

#pragma once

#include "midori/scene/lighting/Lights.h"

#include <glm/glm.hpp>
#include <vector>

namespace midori {

    class LightingManager {
    public:
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
