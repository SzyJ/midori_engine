// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: SceneObject.cpp
// Date: 04/11/2019

#include "mdpch.h"
#include "midori/scene/SceneObject.h"
#include "midori/renderer/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace midori {

    void SceneObject::AddChild(const ref<SceneObject>& child) {
        m_ChildObjects.push_back(child);
    }

    bool SceneObject::DeleteChild(const ref<SceneObject>& child) {
        auto childIndex = std::find(m_ChildObjects.begin(), m_ChildObjects.end(), child);
        if (childIndex == m_ChildObjects.end()) {
            MD_CORE_TRACE("Attempt to remove child scene object that cannot be found");
            return false;
        }

        m_ChildObjects.erase(childIndex);
        return true;
    }

    void SceneObject::SetPosition(const glm::vec3& newPosition) {
        m_Position = newPosition;
        RecalculateTranslate();
    }

    void SceneObject::SetRotation(const glm::vec3& newRotation) {
        m_Rotation = newRotation;
        RecalculateRotate();
    }

    void SceneObject::SetScale(const float newScale) {
        m_Scale = newScale;
        RecalculateScale();
    }

    inline void SceneObject::RecalculateScale() {
        m_ScaleTransform = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale));
        RecalculateTransform();
    }

    inline void SceneObject::RecalculateRotate() {
        glm::mat4 rotationMat(1.0f);
        rotationMat = glm::rotate(rotationMat, m_Rotation.z * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
        rotationMat = glm::rotate(rotationMat, m_Rotation.y * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMat = glm::rotate(rotationMat, m_Rotation.x * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
        m_RotationTransform = rotationMat;
        RecalculateTransform();
    }
   
    inline void SceneObject::RecalculateTranslate() {
        m_TranslateTransform = glm::translate(glm::mat4(1.0f), m_Position);
        RecalculateTransform();
    }

    inline void SceneObject::RecalculateTransform() {
        m_Transform = m_TranslateTransform * m_RotationTransform * m_ScaleTransform;
    }

    void SceneObject::Draw(const glm::mat4& transformMod) const {
        for (const ref<SceneObject>& child : m_ChildObjects) {
            child->Draw(m_Transform * transformMod);
        }

        switch(m_Primitive) {
        case GeometryPrimitive::Triangles:
            Renderer::Submit(m_Shader, m_VertexArray, m_Transform * transformMod, m_Material);
            break;
        case GeometryPrimitive::QuadPatches:
            Renderer::SubmitPatches(m_Shader, m_VertexArray, m_Transform * transformMod);
            break;
        case GeometryPrimitive::TrianglePatches:
            Renderer::SubmitPatches(m_Shader, m_VertexArray, m_Transform * transformMod, 3);
            break;
        }
    }

    void SceneObject::DrawDepth(ref<Shader> depthMapShader, const glm::mat4& transformMod) const {
        for (const ref<SceneObject>& child : m_ChildObjects) {
            child->Draw(m_Transform * transformMod);
        }

        // TODO: Add shadows to patches
        switch (m_Primitive) {
        case GeometryPrimitive::Triangles:
            Renderer::SubmitPositions(depthMapShader, m_VertexArray, m_Transform * transformMod);
            break;
        case GeometryPrimitive::QuadPatches:
            break;
        case GeometryPrimitive::TrianglePatches:
            break;
        }
    }
};
