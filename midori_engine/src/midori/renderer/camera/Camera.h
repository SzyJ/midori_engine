#pragma once
#include "midori/events/KeyEvent.h"
#include "midori/events/MouseEvent.h"

#include <glm/glm.hpp>

namespace midori {
    class Camera {
    public:
        virtual ~Camera() = default;

        virtual void OnWindowResize(unsigned int newWidth, unsigned int newHeight) {}

        virtual const glm::mat4& GetViewMatrix() const = 0;
        virtual const glm::mat4& GetProjectionMatrix() const = 0;
        virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
    };
}