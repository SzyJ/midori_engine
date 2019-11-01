// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Application.cpp
// Date: 03/10/2019

#include "mdpch.h"
#include "Application.h"

#include "midori/core/DeltaTime.h"

#include <GLFW/glfw3.h>

namespace midori {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        if (!s_Instance) {
            s_Instance = this;
        } // else error ???

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(MD_BIND_FUNCTION(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application& Application::Get() {
        if (s_Instance) {
            return *s_Instance;
        }

        return *(s_Instance = new Application());
    }

    void Application::Run() {
        DeltaTime delta;
        float lastFrameTime = 0.0f;
        float thisFrameTime;

        while (m_Running) {
            thisFrameTime = (float) glfwGetTime();
            delta = thisFrameTime - lastFrameTime;
            lastFrameTime = thisFrameTime;

            // Layer Updates
            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate(delta);
            }

            // ImGui Updates
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>(MD_BIND_FUNCTION(Application::OnWindowClose));

        for (auto stackIndex = m_LayerStack.end(); stackIndex != m_LayerStack.begin();) {
            (*--stackIndex)->OnEvent(event);
            if (event.IsHandled()) {
                break;
            }
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& closeEvent) {
        m_Running = false;

        return true;
    }

}
