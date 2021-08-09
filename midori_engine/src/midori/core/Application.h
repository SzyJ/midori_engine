// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Application.h
// Date: 03/10/2019

#pragma once

#include "midori/core/Core.h"
#include "midori/core/Window.h"

#include "midori/events/ApplicationEvent.h"

#include "midori/layers/LayerStack.h"
#include "midori/layers/imgui/ImGuiLayer.h"

#include "midori/world/World.h"

namespace midori {

    class MIDORI_API Application {
    public:
        Application();
        virtual ~Application() = default;

        static Application& Get();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        void SetWorld(ref<World>& newWorld);

        inline Window& GetWindow() { return *m_Window; }

    private:
        static Application* s_Instance;
        ImGuiLayer* m_ImGuiLayer;
        scope<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

        ref<World> m_LoadedWorld;

        bool OnWindowClose(WindowCloseEvent& closeEvent);
    };

    // To be defined in client
    Application* CreateApplication();

}
