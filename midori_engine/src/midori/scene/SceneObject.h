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

    enum class GeometryPrimitive {
        Triangles,
        QuadPatches,
        TrianglePatches
    };

    class SceneObject {
    public:
        SceneObject()
            : m_Position(0.0f),
              m_Rotation(0.0f),
              m_Scale(1.0f) {
            RecalculateScale();
            RecalculateRotate();
            RecalculateTranslate();
        }

        SceneObject(const SceneObject& copy)
            : m_VertexArray(copy.m_VertexArray),
              m_Shader(copy.m_Shader),
              m_Rotation(copy.m_Rotation),
              m_Position(copy.m_Position),
              m_Scale(copy.m_Scale) {
            for (const ref<SceneObject>& child : copy.m_ChildObjects) {
                m_ChildObjects.emplace_back(child);
            }

            RecalculateScale();
            RecalculateRotate();
            RecalculateTranslate();
        }

        virtual ~SceneObject() = default;

        void AddChild(const ref<SceneObject>& child);
        bool DeleteChild(const ref<SceneObject>& child);

        void SetGeometryPrimitive(const GeometryPrimitive newPrimitive) { m_Primitive = newPrimitive; }
        void SetVertexArray(const ref<VertexArray>& vertexArray) { m_VertexArray = vertexArray; }

        void SetShader(const ref<Shader>& shader) { m_Shader = shader; }

        void SetPosition(const glm::vec3& newPosition);
        void SetRotation(const glm::vec3& newRotation);
        void SetScale(const float newScale);

        glm::mat4 GetTransform() const { return m_Transform; }
        float GetDistTo(const glm::vec3& distanceTo) const { return glm::distance(m_Position, distanceTo); }

        void Draw(const glm::mat4& transformMod = glm::mat4(1.0f)) const;

    private:
        GeometryPrimitive m_Primitive = GeometryPrimitive::Triangles;
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
