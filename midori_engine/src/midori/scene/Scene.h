// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Scene.h
// Date: 04/11/2019

#pragma once

#include "midori/core/Core.h"
#include "midori/renderer/camera/Camera.h"
#include "midori/scene/SceneObject.h"

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

        void SetCamera(Camera* camera) { m_Camera = camera; }

        void Draw();

    private:
        Camera* m_Camera;
        std::vector<ref<SceneObject>> m_OpaqueObjects;
        std::vector<ref<SceneObject>> m_AlphaObjects;

        void SortBasedOnDistance(std::vector<ref<SceneObject>>::iterator begin, std::vector<ref<SceneObject>>::iterator end) {
            std::sort(begin, end,
           [this](ref<SceneObject> const &lhs, ref<SceneObject> const& rhs) {
                    glm::vec3 pos = this->m_Camera->GetPosition();
                    return lhs->GetDistTo(pos) < rhs->GetDistTo(pos);
                });
        }
    };

}
