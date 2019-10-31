// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PerspectiveCamera.h
// Date: 31/10/2019

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace midori {

    enum class MovementDirection {
        forward,
        backward,
        left,
        right
    };

    class PerspectiveCamera {
    private:
        const inline static float c_DefaultYaw = -90.0f;
        const inline static float c_DefaultPitch = 0.0f;
        const inline static float c_DefaultZoom = 45.0f;

    public:
        ~PerspectiveCamera() = default;
        PerspectiveCamera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = c_DefaultYaw,
            float pitch = c_DefaultPitch
        );

        glm::mat4 GetViewMatrix() const;

        void Move(MovementDirection direction, float distance);
        void Rotate(float xOffset, float yOffset);
        void Zoom(float zoomAmount);

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        const glm::vec3 m_WorldUp;

        float m_Yaw;
        float m_Pitch;

        float m_Zoom;

        inline void UpdateCameraVectors();
    };

}
