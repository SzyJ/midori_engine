// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PerspectiveCamera.cpp
// Date: 31/10/2019

#include "mdpch.h"
#include "PerspectiveCamera.h"

namespace midori {
    PerspectiveCamera::PerspectiveCamera(float aspectRatio, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : m_AspectRatio(aspectRatio), m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch) {
        UpdateCameraVectors();
        RecalculateViewMatrix();
        RecalculateProjectionMatrix();
    }

    const glm::mat4& PerspectiveCamera::GetViewMatrix() const {
        return m_ViewMatrix;
    }

    const glm::mat4& PerspectiveCamera::GetProjectionMatrix() const {
        return m_ProjectionMatrix;
    }

    const glm::mat4& PerspectiveCamera::GetViewProjectionMatrix() const {
        return m_ViewProjectionMatrix;
    }

    void PerspectiveCamera::OnWindowResize(unsigned int newWidth, unsigned int newHeight) {
        SetAspectRatio((float) newWidth / (float) newHeight);
    }

    void PerspectiveCamera::Move(MovementDirection direction, float distance) {
        if (direction == MovementDirection::forward) {
            m_Position += m_Front * distance;
        }
        if (direction == MovementDirection::backward) {
            m_Position -= m_Front * distance;
        }
        if (direction == MovementDirection::left) {
            m_Position -= m_Right * distance;
        }
        if (direction == MovementDirection::right) {
            m_Position += m_Right * distance;
        }
        if (direction == MovementDirection::up) {
            m_Position += m_WorldUp * distance;
        }
        if (direction == MovementDirection::down) {
            m_Position -= m_WorldUp * distance;
        }

        RecalculateViewMatrix();
    }

    void PerspectiveCamera::Rotate(float xOffset, float yOffset) {
        m_Yaw += xOffset;
        m_Pitch += yOffset;

        if (m_Pitch > 89.0f) {
            m_Pitch = 89.0f;
        } else if (m_Pitch < -89.0f) {
            m_Pitch = -89.0f;
        }

        UpdateCameraVectors();
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::Zoom(float zoomAmount) {
        if (m_Zoom >= 1.0f && m_Zoom <= 45.0f) {
            m_Zoom -= zoomAmount;
        } else if (m_Zoom <= 1.0f) {
            m_Zoom = 1.0f;
        } else if (m_Zoom >= 45.0f) {
            m_Zoom = 45.0f;
        }
        RecalculateProjectionMatrix();
    }

    void PerspectiveCamera::SetAspectRatio(const float aspectRatio) {
        m_AspectRatio = aspectRatio;
        RecalculateProjectionMatrix();
    }
    void PerspectiveCamera::SetNearZ(const float nearZ) {
        m_NearZ = nearZ;
        RecalculateProjectionMatrix();
    }
    void PerspectiveCamera::SetFarZ(const float farZ) {
        m_FarZ = farZ;
        RecalculateProjectionMatrix();
    }

    void PerspectiveCamera::UpdateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);

        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }

    inline void PerspectiveCamera::RecalculateViewMatrix() {
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    inline void PerspectiveCamera::RecalculateProjectionMatrix() {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Zoom), m_AspectRatio, m_NearZ, m_FarZ);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

}
