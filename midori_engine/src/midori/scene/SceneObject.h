// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: SceneObject.h
// Date: 04/11/2019

#pragma once

#include "midori/core/Core.h"
#include "midori/renderer/VertexArray.h"
#include "midori/renderer/Shader.h"
#include "midori/renderer/camera/Camera.h"

#include <vector>


namespace midori {

    class SceneObject {
    public:
        SceneObject()
            : m_Transform(1.0f), m_Position(0.0f) {}

        SceneObject(const SceneObject& copy)
            : m_VertexArray(copy.m_VertexArray),
              m_Shader(copy.m_Shader),
              m_Transform(copy.m_Transform),
              m_Position(copy.m_Position) {
            for (const ref<SceneObject>& child : copy.m_ChildObjects) {
                m_ChildObjects.emplace_back(child);
            }
        }

        virtual ~SceneObject() = default;

        void AddChild(const ref<SceneObject>& child);
        bool DeleteChild(const ref<SceneObject>& child);

        void SetVertexArray(const ref<VertexArray>& vertexArray) { m_VertexArray = vertexArray; }

        void SetShader(const ref<Shader>& shader) { m_Shader = shader; }

        void SetPosition(const glm::vec3& newPosition);
        void SetRotation(const glm::vec3& newRotation);
        void SetScale(const float newScale);

        glm::mat4 GetTransform() const { return m_Transform; }
        float GetDistTo(const glm::vec3& distanceTo) const { return glm::distance(m_Position, distanceTo); }

        void Draw() const;

    private:
        std::vector<ref<SceneObject>> m_ChildObjects;

        ref<VertexArray> m_VertexArray;

        ref<Shader> m_Shader;

        glm::mat4 m_ScaleTransform;
        glm::mat4 m_RotationTransform;
        glm::mat4 m_TranslateTransform;
        glm::mat4 m_Transform;

        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        float m_Scale;

        inline void RecalculateScale();
        inline void RecalculateRotate();
        inline void RecalculateTranslate();
        inline void RecalculateTransform();
    };

}
