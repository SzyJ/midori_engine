// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Light.cpp
// Date: 12/11/2019

#include "mdpch.h"
#include "Light.h"

namespace midori {

    Light::Light(const glm::vec3& position, const glm::vec4& color)
        :m_Position(position), m_Color(color) {
        
    }

}
