// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: SandApp.cpp
// Date: 09/10/2019

#include "Core.h"
#include <Midori.h>
#include "imgui/imgui.h"

class ExampleLayer : public midori::Layer {
public:
    ExampleLayer() : Layer("Test_Layer") {
        midori::Application::Get().GetWindow().SetCursorEnabled(m_CursorEnabled);

        unsigned int screenWidth = midori::Application::Get().GetWindow().GetWindowWidth();
        unsigned int screenHeight = midori::Application::Get().GetWindow().GetWindowHeight();

        m_Camera = new midori::PerspectiveCamera((float) screenWidth / (float) screenHeight, glm::vec3(0.0f, 0.0f, 5.0f));

        m_TestScene.SetCamera(m_Camera);

        // Temporary triangle
        m_VertexArray = midori::VertexArray::Create();

        float vertices[4 * 7] = {
           -0.5f, -0.5f, 1.0f,   0.0f, 0.0f, // [x, y, z], [texX, texY]
            0.5f, -0.5f, 1.0f,   1.0f, 0.0f, // [x, y, z], [texX, texY]
            0.5f,  0.5f, 1.0f,   1.0f, 1.0f, // [x, y, z], [texX, texY]
           -0.5f,  0.5f, 1.0f,   0.0f, 1.0f  // [x, y, z], [texX, texY]
        };

        midori::ref<midori::VertexBuffer> vertexBuffer;
        vertexBuffer = midori::VertexBuffer::Create(vertices, sizeof(vertices));
        midori::BufferLayout layout = {
            { midori::ShaderDataType::Float3, "a_Position" },
            { midori::ShaderDataType::Float2, "a_TexCoord" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        const uint32_t INDEX_COUNT = 6;
        uint32_t indices[INDEX_COUNT] = { 0, 1, 2, 2, 3, 0};
        midori::ref<midori::IndexBuffer> indexBuffer;
        indexBuffer = midori::IndexBuffer::Create(indices, INDEX_COUNT);
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA = (midori::VertexArray::Create());
        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        midori::ref<midori::VertexBuffer> squareVB;
        squareVB = midori::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
        squareVB->SetLayout({
            { midori::ShaderDataType::Float3, "a_Position" }
            });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        midori::ref<midori::IndexBuffer> squareIB;
        squareIB = midori::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        m_SquareVA->SetIndexBuffer(squareIB);

        m_Shader = midori::Shader::Load(SHADER_TEXTURE_SQUARE);
        m_BlueShader = midori::Shader::Load(SHADER_SQUARE_GRID);

        m_TextureCrate = midori::Texture2D::Create(TEXTURE_CRATE);
        m_Shader->Bind();
        m_Shader->UploadUniformInt("u_TextureCrate", TEXTURE_CRATE_ID);

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                glm::vec3 pos(x * 0.11f, y * 0.11f, (x + y) * 0.11f * 0.5f);

                auto thisObject = std::make_shared<midori::SceneObject>();
                thisObject->SetScale(0.1f);
                thisObject->SetPosition(pos);
                thisObject->SetRotation(pos);
                thisObject->SetShader(m_BlueShader);
                thisObject->SetVertexArray(m_SquareVA);

                m_TestScene.AddOpaqueObject(thisObject);
            }
        }

        m_TextureCrate->Bind(TEXTURE_CRATE_ID);
        for (int z = 0; z < 6; ++z) {
            glm::vec3 trans = glm::vec3(0.0f, 0.0f, -3.5f + (1.0f * z));

            auto thisObject = std::make_shared<midori::SceneObject>();
            thisObject->SetPosition(trans);
            thisObject->SetRotation(trans);
            thisObject->SetShader(m_Shader);
            thisObject->SetVertexArray(m_VertexArray);

            m_TestScene.AddAlphaObject(thisObject);

        }


        midori::RenderCommand::Init();
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
        m_DeltaAverage = (m_DeltaAverage * CONF_FPS_SMOOTHING) + (delta * (1.0f - CONF_FPS_SMOOTHING));

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

        m_TestScene.Draw();
    }

    void OnImGuiRender() override {
        ImGui::Begin("FPS");
        ImGui::Text(std::to_string((1.0f/m_DeltaAverage)).c_str());
        ImGui::End();
    }

    void OnEvent(midori::Event& event) override {
        switch(event.GetEventType()) {
        case midori::EventType::WindowResize:
            OnWindowResize((midori::WindowResizeEvent&) event);
            break;

        case midori::EventType::MouseMoved:
            if (!m_CursorEnabled) {
                auto& moveEvent = (midori::MouseMovedEvent&) event;
                m_Camera->Rotate(m_LookSens * moveEvent.GetX(), m_LookSens * moveEvent.GetY());
            }
            break;

        case midori::EventType::KeyPressed:
            auto& keyPressedEvent = (midori::KeyPressedEvent&) event;
            if (keyPressedEvent.GetKeyCode() == MD_KEY_ESCAPE) {
                midori::Application::Get().GetWindow().SetCursorEnabled(m_CursorEnabled = !m_CursorEnabled);
            }
            break;
        }
    }

private:
    midori::DeltaTime m_DeltaAverage = 0.0f;
    midori::ref<midori::Shader> m_Shader;
    midori::ref<midori::VertexArray> m_VertexArray;

    midori::ref<midori::Shader> m_BlueShader;
    midori::ref<midori::VertexArray> m_SquareVA;

    midori::ref<midori::Texture2D> m_TextureCrate;

    midori::Scene m_TestScene;

    midori::PerspectiveCamera* m_Camera;
    float m_MoveSpeed = 2.5f;
    float m_LookSens = 0.1f;

    bool m_CursorEnabled = false;

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
