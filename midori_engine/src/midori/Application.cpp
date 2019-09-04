#include "mdpch.h"
#include "Application.h"

#include "glfw/glfw3.h"

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Midori {

    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());

        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
    }

    Application::~Application() {}

    void Application::Run() {
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));

        MD_TRACE("Dispatched: {0}", event);

    }

    bool Application::OnWindowClose(WindowCloseEvent& closeEvent) {
        m_Running = false;

        return true;
    }

}
