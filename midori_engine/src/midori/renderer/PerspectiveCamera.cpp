// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PerspectiveCamera.cpp
// Date: 31/10/2019

#include "mdpch.h"
#include "PerspectiveCamera.h"

namespace midori {
    PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_Zoom(c_DefaultZoom)  {
        UpdateCameraVectors();
    }

    glm::mat4 PerspectiveCamera::GetViewMatrix() const {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
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
    }

    void PerspectiveCamera::Rotate(float xOffset, float yOffset) {
        m_Yaw += xOffset;
        m_Pitch += yOffset;

        glm::clamp(m_Pitch, -89.0f, 89.0f);

        UpdateCameraVectors();
    }

    void PerspectiveCamera::Zoom(float zoomAmount) {
        if (m_Zoom >= 1.0f && m_Zoom <= 45.0f) {
            m_Zoom -= zoomAmount;
        } else if (m_Zoom <= 1.0f) {
            m_Zoom = 1.0f;
        } else if (m_Zoom >= 45.0f) {
            m_Zoom = 45.0f;
        }
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

}
