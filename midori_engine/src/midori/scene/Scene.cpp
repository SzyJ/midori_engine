// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Scene.cpp
// Date: 04/11/2019

#include "mdpch.h"
#include "Scene.h"

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
            MD_CORE_TRACE("Attempt to remove child scene object that cannot be found");
            return false;
        }

        m_OpaqueObjects.erase(childIndex);
        return true;
    }

    bool Scene::RemoveAlphaObject(const ref<SceneObject>& object)  {
        auto childIndex = std::find(m_AlphaObjects.begin(), m_AlphaObjects.end(), object);
        if (childIndex == m_AlphaObjects.end()) {
            MD_CORE_TRACE("Attempt to remove child scene object that cannot be found");
            return false;
        }

        m_AlphaObjects.erase(childIndex);
        return true;
    }

    void Scene::Draw() {
        // TODO: make this insertion sort
        SortBasedOnDistance(m_Camera->GetPosition(), m_OpaqueObjects.begin(), m_OpaqueObjects.end());
        for (const ref<SceneObject>& obj : m_OpaqueObjects) {
            obj->Draw();
        }

        // TODO: make this insertion sort
        SortBasedOnDistance(m_Camera->GetPosition(), m_AlphaObjects.begin(), m_AlphaObjects.end());
        for (auto it = m_AlphaObjects.end(); it >= m_AlphaObjects.begin(); --it) {
            (*it)->Draw();
        }
    }

};
