// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: RenderScene.h
// Date: 06/08/2021

#pragma once

#include "midori/core/Core.h"
#include "midori/renderer/camera/Camera.h"
#include "midori/renderer/scene/Skybox.h"
#include "midori/renderer/scene/RenderObject.h"
#include "midori/renderer/scene/lighting/LightingManager.h"
#include "midori/renderer/Renderer.h"

#include <vector>
#include <algorithm>

namespace midori {

    class RenderScene {
    public:
        RenderScene() = default;
        ~RenderScene() = default;

        void AddOpaqueObject(const ref<RenderObject>& newObject);
        void AddAlphaObject(const ref<RenderObject>& newObject);
        bool RemoveOpaqueObject(const ref<RenderObject>& object);
        bool RemoveAlphaObject(const ref<RenderObject>& object);

        void SetSkybox(const ref<Skybox>& newSkybox) { m_Skybox = newSkybox; }

        void SetLightManager(const ref<LightingManager>& newLights) {
            m_LightingManager = newLights;
            Renderer::SetLights(newLights);
        }

        void SetCamera(Camera* camera) { m_Camera = camera; }

        void Draw();

        void DrawDepth();

    private:
        Camera* m_Camera;
        ref<Skybox> m_Skybox;

        std::vector<ref<RenderObject>> m_OpaqueObjects;
        std::vector<ref<RenderObject>> m_AlphaObjects;

        ref<LightingManager> m_LightingManager;

        inline void SortBasedOnCameraDistance(std::vector<ref<RenderObject>>::iterator begin, std::vector<ref<RenderObject>>::iterator end) {
            // TODO: Make this insertion sort
            std::sort(begin, end,
                [this](ref<RenderObject> const &lhs, ref<RenderObject> const& rhs) {
                    glm::vec3 pos = m_Camera->GetPosition();
                    return lhs->GetDistTo(pos) < rhs->GetDistTo(pos);
                });
        }
    };

}
