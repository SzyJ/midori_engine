// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Application.cpp
// Date: 03/10/2019

#include "mdpch.h"
#include "Application.h"

#include "midori/renderer/Buffer.h"
#include "midori/renderer/Renderer.h"

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

        m_Camera = new PerspectiveCamera();

        // Temporary triangle
        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, // [x, y, z], [r, g, b, a]
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, // [x, y, z], [r, g, b, a]
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f  // [x, y, z], [r, g, b, a]
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        const uint32_t INDEX_COUNT = 3;
        uint32_t indices[INDEX_COUNT] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(midori::IndexBuffer::Create(indices, INDEX_COUNT));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(VertexArray::Create());
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
            });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        // Set up shader
        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);    
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main() {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                //color = v_Color;
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            void main() {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main() {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    Application& Application::Get() {
        if (s_Instance) {
            return *s_Instance;
        }

        return *(s_Instance = new Application());
    }

    void Application::Run() {
        while (m_Running) {
            // Render Scene
            RenderCommand::SetClearColor({ 0.26f, 0.26f, 0.26f, 1.0f });
            RenderCommand::Clear();

            Renderer::BeginScene(m_Camera);

            Renderer::Submit(m_BlueShader, m_SquareVA);

            Renderer::Submit(m_Shader, m_VertexArray);

            Renderer::EndScene();

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
        const auto newWidth = resizeEvent.GetWidth();
        const auto newHeight = resizeEvent.GetHeight();
        RenderCommand::SetViewport(0, 0, newWidth, newHeight);
        m_Camera->OnWindowResize(newWidth, newHeight);

        return false;
    }
}
