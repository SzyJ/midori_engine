// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: RenderScene.cpp
// Date: 06/08/2021

#include "mdpch.h"
#include "RenderScene.h"

namespace midori {

    void RenderScene::AddOpaqueObject(const ref<RenderObject>& newObject) {
        m_OpaqueObjects.push_back(newObject);
    }

    void RenderScene::AddAlphaObject(const ref<RenderObject>& newObject) {
        m_AlphaObjects.push_back(newObject);
    }

    bool RenderScene::RemoveOpaqueObject(const ref<RenderObject>& object) {
        auto childIndex = std::find(m_OpaqueObjects.begin(), m_OpaqueObjects.end(), object);
        if (childIndex == m_OpaqueObjects.end()) {
            MD_CORE_TRACE("Attempt to remove scene object that cannot be found");
            return false;
        }

        m_OpaqueObjects.erase(childIndex);
        return true;
    }

    bool RenderScene::RemoveAlphaObject(const ref<RenderObject>& object)  {
        auto childIndex = std::find(m_AlphaObjects.begin(), m_AlphaObjects.end(), object);
        if (childIndex == m_AlphaObjects.end()) {
            MD_CORE_TRACE("Attempt to remove scene object that cannot be found");
            return false;
        }

        m_AlphaObjects.erase(childIndex);
        return true;
    }

    void RenderScene::Draw() {
        Renderer::BeginScene(m_Camera);

        if (m_Skybox) {
            m_Skybox->Draw();
        }

        if (!m_OpaqueObjects.empty()) {
            SortBasedOnCameraDistance(m_OpaqueObjects.begin(), m_OpaqueObjects.end());
            for (const ref<RenderObject>& obj : m_OpaqueObjects) {
                obj->Draw();
            }
        }

        if (!m_AlphaObjects.empty()) {
            SortBasedOnCameraDistance(m_AlphaObjects.begin(), m_AlphaObjects.end());
            for (auto it = m_AlphaObjects.rbegin(); it != m_AlphaObjects.rend(); ++it) {
                (*it)->Draw();
            }
        }

        Renderer::EndScene();
    }

    void RenderScene::DrawDepth() {
        uint32_t indexCounter = 0;
        for (const ref<SpotLight>& spotlight : m_LightingManager->GetSpotLights()) {
            if (!spotlight->ShadowMap.IsInitialized()) {
                continue;
            }
            spotlight->ShadowMap.BeginShadowMapPerspectiveScene(indexCounter++, spotlight->Position, spotlight->Direction);

            if (!m_OpaqueObjects.empty()) {
                for (const ref<RenderObject>& obj : m_OpaqueObjects) {
                    obj->DrawDepth(ShadowMap::GetShader());
                }
            }

            spotlight->ShadowMap.EndShadowMapScene();
        }

        indexCounter = 0;
        for (const ref<DirectionalLight>& dirLight : m_LightingManager->GetDirectionalLights()) {
            if (!dirLight->ShadowMap.IsInitialized()) {
                continue;
            }
            dirLight->ShadowMap.BeginShadowMapOrthoScene(indexCounter++, dirLight->Direction);

            if (!m_OpaqueObjects.empty()) {
                for (const ref<RenderObject>& obj : m_OpaqueObjects) {
                    obj->DrawDepth(ShadowMap::GetShader());
                }
            }

            dirLight->ShadowMap.EndShadowMapScene();
        }
    }

};
