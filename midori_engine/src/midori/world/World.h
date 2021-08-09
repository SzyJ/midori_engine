// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: World.h
// Date: 08/08/2021

#pragma once

#include "midori/core/DeltaTime.h"
#include "midori/layers/Layer.h"
#include "midori/renderer/camera/PerspectiveCamera.h"
#include "midori/renderer/scene/RenderScene.h"
#include "midori/renderer/post-processing/PostProcessingPipeline.h"
#include "midori/events/Event.h"

namespace midori {

    class World {
    public:
        World();

        void Update(DeltaTime delta);
        void OnEvent(Event& event);
        void DrawScene();

        // Camera control interface
        void Camera_Rotate(float xOffset, float yOffset) { m_Camera.Rotate(xOffset, yOffset); }
        void Camera_Move(MovementDirection direction, float distance) { m_Camera.Move(direction, distance); }
        void Camera_Zoom(float zoomAmount) { m_Camera.Zoom(zoomAmount); }
        void Camera_SetAspectRatio(float aspectRatio) { m_Camera.SetAspectRatio(aspectRatio); }
        void Camera_SetNearZ(const float nearZ) { m_Camera.SetNearZ(nearZ); }
        void Camera_SetFarZ(const float farZ) { m_Camera.SetFarZ(farZ); }

        // Lighting interface
        void Lighting_AddPointLight(const ref<PointLight>& newLight) { m_LightManager->AddPointLight(newLight); }
        void Lighting_AddDirectionalLight(const ref<DirectionalLight>& newLight) { m_LightManager->AddDirectionalLight(newLight); }
        void Lighting_AddSpotLight(const ref<SpotLight>& newLight) { m_LightManager->AddSpotLight(newLight); }

        // Post-Processing Interface
        void PostProcessing_AddStage(const char* shaderPath) { m_PostProcessing.AddStage(shaderPath); }

        // Scene Interface
        void Scene_AddOpaqueObject(const ref<RenderObject>& newObject) { m_Scene.AddOpaqueObject(newObject); }
        void Scene_AddAlphaObject(const ref<RenderObject>& newObject) { m_Scene.AddAlphaObject(newObject); }

    private:
        DeltaTime m_TimeRunning = 0.0f;
        //std::vector<ref<EntityBase>> m_WorldEntities;

        RenderScene m_Scene;
        PerspectiveCamera m_Camera;
        ref<LightingManager> m_LightManager;
        PostProcessingPipeline m_PostProcessing;
    };

}