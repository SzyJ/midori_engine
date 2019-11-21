// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Scene.h
// Date: 04/11/2019

#pragma once

#include "midori/core/Core.h"
#include "midori/renderer/camera/Camera.h"
#include "midori/scene/Skybox.h"
#include "midori/scene/SceneObject.h"
#include "midori/scene/lighting/LightingManager.h"
#include "midori/renderer/Renderer.h"

#include <vector>

namespace midori {

    class Scene {
    public:
        Scene() = default;
        ~Scene() = default;

        void AddOpaqueObject(const ref<SceneObject>& newObject);
        void AddAlphaObject(const ref<SceneObject>& newObject);
        bool RemoveOpaqueObject(const ref<SceneObject>& object);
        bool RemoveAlphaObject(const ref<SceneObject>& object);

        void SetSkybox(Skybox* newSkybox) { m_Skybox = newSkybox; }

        void SetLightManager(const ref<LightingManager>& newLights) {
            m_LightingManager = newLights;
            Renderer::SetLights(newLights);
        }

        void SetCamera(Camera* camera) { m_Camera = camera; }

        void Draw();

        void DrawDepth();

    private:
        Camera* m_Camera;
        Skybox* m_Skybox;

        std::vector<ref<SceneObject>> m_OpaqueObjects;
        std::vector<ref<SceneObject>> m_AlphaObjects;

        ref<LightingManager> m_LightingManager;

        inline void SortBasedOnCameraDistance(std::vector<ref<SceneObject>>::iterator begin, std::vector<ref<SceneObject>>::iterator end) {
            // TODO: Make this insertion sort
            std::sort(begin, end,
                [this](ref<SceneObject> const &lhs, ref<SceneObject> const& rhs) {
                    glm::vec3 pos = m_Camera->GetPosition();
                    return lhs->GetDistTo(pos) < rhs->GetDistTo(pos);
                });
        }
    };

}
