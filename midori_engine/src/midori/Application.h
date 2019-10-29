// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Application.h
// Date: 03/10/2019

#pragma once

#include "midori/Core.h"
#include "midori/Window.h"

#include "midori/events/ApplicationEvent.h"

#include "midori/layers/LayerStack.h"
#include "midori/layers/imgui/ImGuiLayer.h"

#include "midori/renderer/Shader.h"
#include "midori/renderer/Buffer.h"

namespace midori {

    class MIDORI_API Application {
    public:
        Application();
        virtual ~Application();

        static Application& Get();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *m_Window; }

    private:
        static Application* s_Instance;
        ImGuiLayer* m_ImGuiLayer;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Shader> m_Shader;
        bool m_Running;
        LayerStack m_LayerStack;

        unsigned int m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;


        bool OnWindowClose(WindowCloseEvent& closeEvent);
        bool OnWindowResize(WindowResizeEvent& resizeEvent);

    };

    // To be defined in client
    Application* CreateApplication();

}
