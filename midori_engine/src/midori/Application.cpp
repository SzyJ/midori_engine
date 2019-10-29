// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Application.cpp
// Date: 03/10/2019

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

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);


        // Temporary triangle
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertices[3 * 3] = {
            -0.5f, -0.5f,  0.0f,
             0.5f, -0.5f,  0.0f,
             0.0f,  0.5f,  0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

        unsigned int indeces[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

        // Set up shader
        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
            glClearColor(0, 0, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            // Layer Updates
            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
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
        dispatcher.Dispatch<WindowResizeEvent>(MD_BIND_FUNCTION(Application::OnWindowResize));

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

    bool Application::OnWindowResize(WindowResizeEvent& resizeEvent) {
        
        glViewport(0, 0, resizeEvent.GetWidth(), resizeEvent.GetHeight());

        return false;
    }
}
