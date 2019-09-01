#pragma once

#include "midori/Core.h"

#include "midori/Window.h"

namespace Midori {

    class MIDORI_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running;
    };

    // To be defined in client
    Application* CreateApplication();

}
