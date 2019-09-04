#pragma once

#include "midori/Core.h"
#include "midori/Window.h"
#include "midori/events/ApplicationEvent.h"

namespace Midori {

    class MIDORI_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running;

        bool OnWindowClose(WindowCloseEvent& closeEvent);
    };

    // To be defined in client
    Application* CreateApplication();

}
