// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: PerspectiveCamera.h
// Date: 31/10/2019

#pragma once

#include "midori/renderer/camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace midori {

    enum class MovementDirection {
        forward,
        backward,
        left,
        right,
        up,
        down,
        world_up,
        world_down,
    };

    class PerspectiveCamera : public Camera {
    private:
        const inline static float c_DefaultYaw = -90.0f;
        const inline static float c_DefaultPitch = 0.0f;
        const inline static float c_DefaultZoom = 45.0f;
        const inline static float c_DefaultNearZ = 0.01f;
        const inline static float c_DefaultFarZ = 100.0f;

    public:
        ~PerspectiveCamera() = default;
        PerspectiveCamera(
            float aspectRatio = 0.0f,
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = c_DefaultYaw,
            float pitch = c_DefaultPitch
        );

        virtual const glm::vec3& GetPosition() const override { return m_Position; }
        virtual const glm::vec3& GetDirection() const override { return m_Front; }
        virtual void SetPosition(const glm::vec3& newPos) override {
            m_Position = newPos;
            RecalculateViewMatrix();
        }
        virtual void SetDirection(float yaw, float pitch) override {
            m_Yaw = yaw;
            m_Pitch = pitch;
            UpdateCameraVectors();
            RecalculateViewMatrix();
        }
        virtual float GetYaw() override { return m_Yaw; }
        virtual float GetPitch() override { return m_Pitch; }

        virtual const glm::mat4& GetViewMatrix() const override;
        virtual const glm::mat4& GetProjectionMatrix() const override;
        virtual const glm::mat4& GetViewProjectionMatrix() const override;

        virtual void OnWindowResize(unsigned int newWidth, unsigned int newHeight) override;

        void Move(MovementDirection direction, float distance);
        void Rotate(float xOffset, float yOffset);
        void Zoom(float zoomAmount);

        void SetAspectRatio(const float aspectRatio);
        void SetNearZ(const float nearZ);
        void SetFarZ(const float farZ);

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        const glm::vec3 m_WorldUp;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        float m_Yaw;
        float m_Pitch;
        float m_Zoom = c_DefaultZoom;

        float m_AspectRatio;
        float m_NearZ = c_DefaultNearZ;
        float m_FarZ = c_DefaultFarZ;

        inline void UpdateCameraVectors();

        inline void RecalculateViewMatrix();
        inline void RecalculateProjectionMatrix();
    };

}
