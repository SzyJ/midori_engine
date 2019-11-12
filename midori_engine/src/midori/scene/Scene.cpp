// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Scene.cpp
// Date: 04/11/2019

#include "mdpch.h"
#include "Scene.h"

#include "midori/renderer/Renderer.h"

namespace midori {

    void Scene::AddOpaqueObject(const ref<SceneObject>& newObject) {
        m_OpaqueObjects.push_back(newObject);
    }

    void Scene::AddAlphaObject(const ref<SceneObject>& newObject) {
        m_AlphaObjects.push_back(newObject);
    }

    bool Scene::RemoveOpaqueObject(const ref<SceneObject>& object) {
        auto childIndex = std::find(m_OpaqueObjects.begin(), m_OpaqueObjects.end(), object);
        if (childIndex == m_OpaqueObjects.end()) {
            MD_CORE_TRACE("Attempt to remove scene object that cannot be found");
            return false;
        }

        m_OpaqueObjects.erase(childIndex);
        return true;
    }

    bool Scene::RemoveAlphaObject(const ref<SceneObject>& object)  {
        auto childIndex = std::find(m_AlphaObjects.begin(), m_AlphaObjects.end(), object);
        if (childIndex == m_AlphaObjects.end()) {
            MD_CORE_TRACE("Attempt to remove scene object that cannot be found");
            return false;
        }

        m_AlphaObjects.erase(childIndex);
        return true;
    }

    void Scene::Draw() {
        Renderer::BeginScene(m_Camera);

        if (m_Skybox) {
            m_Skybox->Draw();
        }

        if (!m_OpaqueObjects.empty()) {
            SortBasedOnCameraDistance(m_OpaqueObjects.begin(), m_OpaqueObjects.end());
            for (const ref<SceneObject>& obj : m_OpaqueObjects) {
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

};
