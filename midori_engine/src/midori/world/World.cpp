// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: World.cpp
// Date: 08/08/2021

#include "mdpch.h"
#include "World.h"

#include "midori/core/Application.h"
#include "midori/renderer/camera/PerspectiveCamera.h"

namespace midori {

    World::World() {
        const unsigned int screenWidth = midori::Application::Get().GetWindow().GetWindowWidth();
        const unsigned int screenHeight = midori::Application::Get().GetWindow().GetWindowHeight();

        m_Camera.OnWindowResize(screenWidth, screenHeight);
        m_PostProcessing.UpdateScreenSize(screenWidth, screenHeight);
        m_LightManager->UpdateFrameBufferSize(screenWidth, screenHeight);

        m_Scene.SetCamera(&m_Camera);
        m_Scene.SetLightManager(m_LightManager);

        RenderCommand::Init();
    }

    void World::Update(DeltaTime delta) {
        m_TimeRunning = m_TimeRunning + delta;
    }

    void World::DrawScene() {
        m_Scene.DrawDepth();

        m_PostProcessing.BeginPostProcess();
        midori::RenderCommand::SetClearColor({ 0.26f, 0.26f, 0.26f, 1.0f });
        midori::RenderCommand::Clear();
        m_Scene.Draw();
        m_PostProcessing.FinishPostProcess(m_TimeRunning);
    }

    void World::OnEvent(Event& event) {
        if (event.GetEventType() == EventType::WindowResize) {
            const auto newWidth = ((midori::WindowResizeEvent&) event).GetWidth();
            const auto newHeight = ((midori::WindowResizeEvent&) event).GetHeight();

            midori::RenderCommand::SetViewport(0, 0, newWidth, newHeight);
            m_Camera.OnWindowResize(newWidth, newHeight);
            m_LightManager->UpdateFrameBufferSize(newWidth, newHeight);
            m_PostProcessing.UpdateScreenSize(newWidth, newHeight);
        }
    }

}