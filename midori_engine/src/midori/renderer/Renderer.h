// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Renderer.h
// Date: 29/10/2019

#pragma once

#include "midori/renderer/camera/Camera.h"
#include "midori/renderer/RenderCommand.h"
#include "midori/renderer/Shader.h"
#include "midori/scene/lighting/LightingManager.h"
#include "midori/scene/lighting/Materials.h"

namespace midori {

    class Renderer {
    public:
        static void BeginScene(Camera* camera);
        static void EndScene();

        static void SetLights(const ref<LightingManager>& lights) { m_SceneData->Lights = lights; }

        static void Submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), const Material& material = Material());
        static void Submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const Material& material);

        static void SubmitPatches(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), uint32_t vertices = 4);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
            glm::mat4 ProjectionMatrix;
            glm::mat4 StaticViewMatrix;

            glm::vec3 CameraPosition;

            ref<LightingManager> Lights = nullptr;
        };

        static SceneData* m_SceneData;
    };

}
