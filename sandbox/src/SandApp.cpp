// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: SandApp.cpp
// Date: 09/10/2019

#include <Midori.h>
#include "imgui/imgui.h"

class ExampleLayer : public midori::Layer {
public:
    ExampleLayer() : Layer("Test_Layer") {

        m_Camera = new midori::PerspectiveCamera();

        // Temporary triangle
       m_VertexArray.reset(midori::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, // [x, y, z], [r, g, b, a]
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, // [x, y, z], [r, g, b, a]
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f  // [x, y, z], [r, g, b, a]
        };

        std::shared_ptr<midori::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(midori::VertexBuffer::Create(vertices, sizeof(vertices)));
        midori::BufferLayout layout = {
            { midori::ShaderDataType::Float3, "a_Position" },
            { midori::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        const uint32_t INDEX_COUNT = 3;
        uint32_t indices[INDEX_COUNT] = { 0, 1, 2 };
        std::shared_ptr<midori::IndexBuffer> indexBuffer;
        indexBuffer.reset(midori::IndexBuffer::Create(indices, INDEX_COUNT));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(midori::VertexArray::Create());
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<midori::VertexBuffer> squareVB;
        squareVB.reset(midori::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { midori::ShaderDataType::Float3, "a_Position" }
            });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<midori::IndexBuffer> squareIB;
        squareIB.reset(midori::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

        m_Shader.reset(new midori::Shader(vertexSrc, fragmentSrc));

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

        m_BlueShader.reset(new midori::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    ~ExampleLayer() {
        delete m_Camera;
    }

    void OnAttach() override {
        MD_INFO("Example Layer Attached");
    }

    void OnDetach() override {
        MD_INFO("Example Layer Detached");
    }

    void OnUpdate(midori::DeltaTime delta) override {
        m_ThisDelta = delta;

        if (midori::Input::IsKeyPressed(MD_KEY_W)) {
            m_Camera->Move(midori::MovementDirection::forward, delta * m_MoveSpeed);
        }
        if (midori::Input::IsKeyPressed(MD_KEY_A)) {
            m_Camera->Move(midori::MovementDirection::left, delta * m_MoveSpeed);
        }
        if (midori::Input::IsKeyPressed(MD_KEY_S)) {
            m_Camera->Move(midori::MovementDirection::backward, delta * m_MoveSpeed);
        }
        if (midori::Input::IsKeyPressed(MD_KEY_D)) {
            m_Camera->Move(midori::MovementDirection::right, delta * m_MoveSpeed);
        }
        if (midori::Input::IsKeyPressed(MD_KEY_SPACE)) {
            m_Camera->Move(midori::MovementDirection::up, delta * m_MoveSpeed);
        }
        if (midori::Input::IsKeyPressed(MD_KEY_LEFT_SHIFT)) {
            m_Camera->Move(midori::MovementDirection::down, delta * m_MoveSpeed);
        }

        midori::RenderCommand::SetClearColor({ 0.26f, 0.26f, 0.26f, 1.0f });
        midori::RenderCommand::Clear();

        midori::Renderer::BeginScene(m_Camera);

        midori::Renderer::Submit(m_BlueShader, m_SquareVA);
        midori::Renderer::Submit(m_Shader, m_VertexArray);

        midori::Renderer::EndScene();
    }

    void OnImGuiRender() override {
        float smoothing = 0.9; // larger=more smoothing
        m_DeltaAverage = (m_DeltaAverage * smoothing) + (m_ThisDelta * (1.0 - smoothing));
        
        ImGui::Begin("FPS");
        ImGui::Text(std::to_string((1.0f/m_DeltaAverage)).c_str());
        ImGui::End();
    }

    void OnEvent(midori::Event& event) override {
        if (event.GetEventType() == midori::EventType::WindowResize) {
            OnWindowResize((midori::WindowResizeEvent&) event);
        }

        if (event.GetEventType() == midori::EventType::MouseMoved) {
            auto& moveEvent = (midori::MouseMovedEvent&) event;
            m_Camera->Rotate(m_LookSens * moveEvent.GetX(), m_LookSens * moveEvent.GetY());
        }
    }

private:
    midori::DeltaTime m_ThisDelta;
    midori::DeltaTime m_DeltaAverage = 0.0f;
    std::shared_ptr<midori::Shader> m_Shader;
    std::shared_ptr<midori::VertexArray> m_VertexArray;

    std::shared_ptr<midori::Shader> m_BlueShader;
    std::shared_ptr<midori::VertexArray> m_SquareVA;

    midori::PerspectiveCamera* m_Camera;
    float m_MoveSpeed = 2.5f;
    float m_LookSens = 0.1f;

    void OnWindowResize(midori::WindowResizeEvent& resizeEvent) {
        const auto newWidth = resizeEvent.GetWidth();
        const auto newHeight = resizeEvent.GetHeight();

        midori::RenderCommand::SetViewport(0, 0, newWidth, newHeight);
        m_Camera->OnWindowResize(newWidth, newHeight);
    }
};

class Sandbox : public midori::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {}
};

midori::Application* midori::CreateApplication() { return new Sandbox(); }
