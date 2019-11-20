// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Camera.h
// Date: 12/11/2019

#pragma once

#include <glm/glm.hpp>

namespace midori {
    class Camera {
    public:
        virtual ~Camera() = default;

        virtual void OnWindowResize(unsigned int newWidth, unsigned int newHeight) {}

        virtual const glm::vec3& GetPosition() const = 0;
        virtual const glm::vec3& GetDirection() const = 0;

        virtual const glm::mat4& GetViewMatrix() const = 0;
        virtual const glm::mat4& GetProjectionMatrix() const = 0;
        virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
    };
}
