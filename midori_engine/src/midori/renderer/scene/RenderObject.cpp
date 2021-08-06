// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: RenderObject.cpp
// Date: 06/08/2021

#include "mdpch.h"
#include "midori/renderer/scene/RenderObject.h"
#include "midori/renderer/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace midori {

    void RenderObject::AddChild(const ref<RenderObject>& child) {
        m_ChildObjects.push_back(child);
    }

    bool RenderObject::DeleteChild(const ref<RenderObject>& child) {
        auto childIndex = std::find(m_ChildObjects.begin(), m_ChildObjects.end(), child);
        if (childIndex == m_ChildObjects.end()) {
            MD_CORE_TRACE("Attempt to remove child scene object that cannot be found");
            return false;
        }

        m_ChildObjects.erase(childIndex);
        return true;
    }

    void RenderObject::SetPosition(const glm::vec3& newPosition) {
        m_Position = newPosition;
        RecalculateTranslate();
    }

    void RenderObject::SetRotation(const glm::vec3& newRotation) {
        m_Rotation = newRotation;
        RecalculateRotate();
    }

    void RenderObject::SetScale(const float newScale) {
        m_Scale = newScale;
        RecalculateScale();
    }

    void RenderObject::RecalculateScale() {
        m_ScaleTransform = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale));
        RecalculateTransform();
    }

    void RenderObject::RecalculateRotate() {
        glm::mat4 rotationMat(1.0f);
        rotationMat = glm::rotate(rotationMat, m_Rotation.z * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
        rotationMat = glm::rotate(rotationMat, m_Rotation.y * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMat = glm::rotate(rotationMat, m_Rotation.x * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
        m_RotationTransform = rotationMat;
        RecalculateTransform();
    }
   
    void RenderObject::RecalculateTranslate() {
        m_TranslateTransform = glm::translate(glm::mat4(1.0f), m_Position);
        RecalculateTransform();
    }

    void RenderObject::RecalculateTransform() {
        m_Transform = m_TranslateTransform * m_RotationTransform * m_ScaleTransform;
    }

    void RenderObject::Draw(const glm::mat4& transformMod) const {
        for (const ref<RenderObject>& child : m_ChildObjects) {
            child->Draw(transformMod * m_Transform);
        }

        switch(m_Primitive) {
        case GeometryPrimitive::Triangles:
            Renderer::Submit(m_Shader, m_VertexArray, transformMod * m_Transform, m_Material);
            break;
        case GeometryPrimitive::QuadPatches:
            Renderer::SubmitPatches(m_Shader, m_VertexArray, transformMod * m_Transform);
            break;
        case GeometryPrimitive::TrianglePatches:
            Renderer::SubmitPatches(m_Shader, m_VertexArray, transformMod * m_Transform, 3);
            break;
        }
    }

    void RenderObject::DrawDepth(ref<Shader> depthMapShader, const glm::mat4& transformMod) const {
        for (const ref<RenderObject>& child : m_ChildObjects) {
            child->DrawDepth(depthMapShader, transformMod * m_Transform);
        }

        // TODO: Add shadows to patches
        switch (m_Primitive) {
        case GeometryPrimitive::Triangles:
            Renderer::SubmitPositions(depthMapShader, m_VertexArray, transformMod * m_Transform);
            break;
        case GeometryPrimitive::QuadPatches:
            break;
        case GeometryPrimitive::TrianglePatches:
            break;
        }
    }
};
