// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PointLight.h
// Date: 12/11/2019

#pragma once

#include "midori/scene/lighting/ShadowMap.h"

#include <glm/glm.hpp>

namespace midori {

    class DirectionalLightShadowMap;

    struct Light {
 
        virtual ~Light() = default;

        glm::vec3 Color;

    protected:
        Light(const glm::vec3& color)
            : Color(color) {}
        Light()
            : Color(1.0f) {}
    };

    struct PointLight : public Light {
        PointLight(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f))
            : Light(color), Position(position) {}

        PointLight(const PointLight& copy)
            : Light(copy.Color), Position(copy.Position) {}

        PointLight()
            : Light(glm::vec3(1.0f)), Position(0.0f) {}

        ~PointLight() = default;

        static inline BufferLayout GetBufferLayout() {
            return BufferLayout({
                {ShaderDataType::Float3, "Color"},
                {ShaderDataType::Float, "LinearAttenuation"},

                {ShaderDataType::Float3, "Position"},
                {ShaderDataType::Float, "QuadraticAttenuation"}
            });
        }

        glm::vec3 Position;
        float LinearAttenuation = 0.14f;
        float QuadraticAttenuation = 0.07f;
    };

    struct DirectionalLight : public Light {
        DirectionalLight(const glm::vec3& direction, const glm::vec3& color = glm::vec3(1.0f))
            : Light(color), Direction(direction) {}

        DirectionalLight(const DirectionalLight& copy)
            : Light(copy.Color), Direction(copy.Direction) {}

        DirectionalLight()
            : Light(glm::vec3(1.0f)), Direction(0.0f, -1.0f, 0.0f) {}

        ~DirectionalLight() = default;

        static inline BufferLayout GetBufferLayout() {
            return BufferLayout({
                {ShaderDataType::Float3, "Color"},
                {ShaderDataType::Float, "Strength"},

                {ShaderDataType::Float3, "Direction"},
                {ShaderDataType::Float, "Padding0"},
                });
        }

        glm::vec3 Direction;
        float Strength = 0.25f;
    };

    struct SpotLight : public Light {
        SpotLight(const glm::vec3& position, const glm::vec3& direction = glm::vec3(0.0f), const glm::vec3& color = glm::vec3(1.0f))
            : Light(color), Position(position), Direction(direction) {}

        SpotLight(const SpotLight& copy)
            : Light(copy.Color), Position(copy.Position), Direction(copy.Direction) {}

        SpotLight()
            : Light(glm::vec3(1.0f)), Position(0.0f), Direction(0.0f, -1.0f, 0.0f) {}

        ~SpotLight() = default;
        static inline BufferLayout GetBufferLayout() {
            return BufferLayout({
                {ShaderDataType::Float3, "Color"},
                {ShaderDataType::Float, "InnerCutoff"},

                {ShaderDataType::Float3, "Position"},
                {ShaderDataType::Float, "OuterCutoff"},

                {ShaderDataType::Float3, "Direction"},
                {ShaderDataType::Float, "DistanceCutoff"}
                });
        }

        glm::vec3 Position;
        glm::vec3 Direction;
        float InnerCutoff = glm::cos(glm::radians(12.5f));
        float OuterCutoff = glm::cos(glm::radians(17.5f));
        float DistanceCutoff = 25.0f;

        DirectionalLightShadowMap ShadowMap;
    };

}
