// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Light.h
// Date: 12/11/2019

#pragma once

#include <glm/glm.hpp>

namespace midori {

    class Light {
    public:
        Light() = delete;
        Light(const glm::vec3& position, const glm::vec4& color);
        ~Light() = default;

        glm::vec3 GetPosition() const { return m_Position; }
        glm::vec4 GetColor() const { return m_Color; }

        void SetPosition(const glm::vec3& newPos) { m_Position = newPos; }

    private:
        glm::vec3 m_Position;
        glm::vec4 m_Color;
    };

}
