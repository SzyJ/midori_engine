// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: SceneObject.h
// Date: 04/11/2019

#pragma once

#include "midori/core/Core.h"
#include "midori/renderer/VertexArray.h"
#include "midori/renderer/Shader.h"

#include <vector>

namespace midori {

    class SceneObject {
    public:
        SceneObject()
            : m_Transform(1.0f), m_Position(0.0f) {}

        virtual ~SceneObject() = default;

        void AddChild(const ref<SceneObject>& child);
        void DeleteChild(const ref<SceneObject>& child);

        void SetVertexArray(const ref<VertexArray>& vertexArray) { m_VertexArray = vertexArray; }

        void SetShader(const ref<Shader>& shader) { m_Shader = shader; }

        void SetTransform(glm::mat4 newTransform) { m_Transform = newTransform; }

        void SetPosition(glm::mat4 newPosition) { m_Position = newPosition; }

        glm::mat4 GetTransform() const { return m_Transform * m_Position; }

        void Draw() const;

    private:
        std::vector<ref<SceneObject>> m_ChildObjects;

        ref<VertexArray> m_VertexArray;

        ref<Shader> m_Shader;

        glm::mat4 m_Transform;

        glm::mat4 m_Position;
    };

}
