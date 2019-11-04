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
        const glm::vec3& camPos = m_Camera->GetPosition();
        auto farToCloseFunc = [=, &camPos](SceneObject* left, SceneObject* right) -> bool {
            return left->GetDistTo(camPos) < right->GetDistTo(camPos);
        };
        auto closeToFarFunc = [=, &camPos](SceneObject* left, SceneObject* right) -> bool {
            return left->GetDistTo(camPos) > right->GetDistTo(camPos);
        };

        // TODO: make this insertion sort
        std::sort(m_AlphaObjects.begin(), m_AlphaObjects.end(), closeToFarFunc);
        for (const ref<SceneObject>& obj : m_OpaqueObjects) {
            obj->Draw();
        }

        // TODO: make this insertion sort
        std::sort(m_AlphaObjects.begin(), m_AlphaObjects.end(), farToCloseFunc);
        for (const ref<SceneObject>& obj : m_AlphaObjects) {
            obj->Draw();
        }
    }

};
