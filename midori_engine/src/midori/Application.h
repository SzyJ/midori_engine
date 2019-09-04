#pragma once

#include "midori/Core.h"
#include "midori/Window.h"
#include "midori/events/ApplicationEvent.h"
#include "midori/layers/LayerStack.h"

namespace Midori {

    class MIDORI_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running;
        LayerStack m_LayerStack;

        bool OnWindowClose(WindowCloseEvent& closeEvent);
    };

    // To be defined in client
    Application* CreateApplication();

}
