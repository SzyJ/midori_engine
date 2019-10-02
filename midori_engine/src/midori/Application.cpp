#include "mdpch.h"
#include "Application.h"
#include <glad/glad.h>

namespace midori {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        if (!s_Instance) {
            s_Instance = this;
        } // else error ???

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(MD_BIND_FUNCTION(Application::OnEvent));
    }

    Application::~Application() {}

    Application& Application::Get() {
        if (s_Instance) {
            return *s_Instance;
        }

        return *(s_Instance = new Application());
    }

    void Application::Run() {
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Window->OnUpdate();

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }
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
