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
        void RemoveOpaqueObject(const ref<SceneObject>& object);
        void RemoveAlphaObject(const ref<SceneObject>& object);

        void SetCamera(const ref<Camera>& camera) { m_Camera = camera; }

        void Draw();

    private:
        ref<Camera> m_Camera;
        std::vector<ref<SceneObject>> m_OpaqueObjects;
        std::vector<ref<SceneObject>> m_AlphaObjects;
    };

}
