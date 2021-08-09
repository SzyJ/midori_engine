// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: EntiyBase.h
// Date: 08/08/2021

#pragma once

#include "midori/core/Core.h"
#include "midori/world/Components/EntityRendererComponent.h"

namespace midori{

    class EntityBase {
    public:
        EntityBase() = default;

    private:
        std::string m_DebugName;

        // Share data with components
        ref<glm::vec3> m_WorldPos;
        ref<glm::vec3> m_WorldRotation;
        ref<float> m_Scale;
    };

}
