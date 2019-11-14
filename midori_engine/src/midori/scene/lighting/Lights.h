// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PointLight.h
// Date: 12/11/2019

#pragma once

#include <glm/glm.hpp>

namespace midori {

    struct Light {
        Light()
            : Color(1.0f) {}

        virtual ~Light() = default;

        glm::vec3 Color;

    protected:
        Light(const glm::vec3& color)
            : Color(color) {}
    };

    struct PointLight : public Light {
        PointLight(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f))
            : Light(color), Position(position) {}

        PointLight(const PointLight& copy)
            : Light(copy.Color), Position(copy.Position) {}

        PointLight()
            : Light(glm::vec3(1.0f)), Position(0.0f) {}

        ~PointLight() = default;

        glm::vec3 Position;
    };

    struct DirectionalLight : public Light {
        DirectionalLight(const glm::vec3& direction, const glm::vec3& color = glm::vec3(1.0f))
            : Light(color), Direction(direction) {}

        DirectionalLight(const DirectionalLight& copy)
            : Light(copy.Color), Direction(copy.Direction) {}

        DirectionalLight()
            : Light(glm::vec3(1.0f)), Direction(0.0f, -1.0f, 0.0f) {}

        ~DirectionalLight() = default;

        glm::vec3 Direction;
    };

    struct SpotLight : public Light {
        SpotLight(const glm::vec3& position, const glm::vec3& direction = glm::vec3(0.0f), const glm::vec3& color = glm::vec3(1.0f))
            : Light(color), Position(position), Direction(direction) {}

        SpotLight(const SpotLight& copy)
            : Light(copy.Color), Position(copy.Position), Direction(copy.Direction) {}

        SpotLight()
            : Light(glm::vec3(1.0f)), Position(0.0f), Direction(0.0f, -1.0f, 0.0f) {}

        ~SpotLight() = default;

        glm::vec3 Position;
        glm::vec3 Direction;
    };

}