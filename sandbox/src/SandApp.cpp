// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: SandApp.cpp
// Date: 09/10/2019

#include "Core.h"
#include <Midori.h>
#include "imgui/imgui.h"

#include <midori/renderer/MeshLoader.h>

class ExampleLayer : public midori::Layer {
public:
    ExampleLayer() : Layer("Test_Layer") {
        midori::Application::Get().GetWindow().SetCursorEnabled(m_CursorEnabled);

        unsigned int screenWidth = midori::Application::Get().GetWindow().GetWindowWidth();
        unsigned int screenHeight = midori::Application::Get().GetWindow().GetWindowHeight();

        m_Camera = new midori::PerspectiveCamera((float) screenWidth / (float) screenHeight, glm::vec3(0.0f, 0.0f, 10.0f));

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

        m_SquareVA = midori::VertexArray::Create();
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

        m_TextureFLogo = midori::Texture2D::Create(TEXTURE_FLOGO);
        m_TextureFLogo->Bind(TEXTURE_FLOGO_ID);

        m_TextureCrate = midori::Texture2D::Create(TEXTURE_CRATE);
        m_TextureCrate->Bind(TEXTURE_CRATE_ID);

        m_Shader->Bind();
        m_Shader->UploadUniformInt("u_TextureFLogo", TEXTURE_FLOGO_ID);
        m_Shader->UploadUniformInt("u_TextureCrate", TEXTURE_CRATE_ID);

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                glm::vec3 pos(x * 0.11f, y * 0.11f, (x + y) * 0.11f * 0.5f);

                auto thisObject = midori::make_ref<midori::SceneObject>();
                thisObject->SetScale(0.1f);
                thisObject->SetPosition(pos);
                thisObject->SetRotation(pos);
                thisObject->SetShader(m_BlueShader);
                thisObject->SetVertexArray(m_SquareVA);

                m_TestScene.AddOpaqueObject(thisObject);
            }
        }

        for (int z = 0; z < 6; ++z) {
            glm::vec3 trans = glm::vec3(0.0f, 0.0f, -3.5f + (1.0f * z));

            auto thisObject = midori::make_ref<midori::SceneObject>();
            thisObject->SetPosition(trans);
            thisObject->SetShader(m_Shader);
            thisObject->SetVertexArray(m_VertexArray);

            m_TestScene.AddAlphaObject(thisObject);
        }

        m_MeshLoadShader = midori::Shader::Load(SHADER_MODEL_LOADER);

        m_MeshLoadShader->Bind();
        m_MeshLoadShader->UploadUniformInt("u_TextureCrate", TEXTURE_CRATE_ID);


        auto modelTeapot = midori::make_ref<midori::SceneObject>();
        modelTeapot->SetShader(m_MeshLoadShader);
        modelTeapot->SetVertexArray(midori::MeshLoader::Load(MODEL_TEAPOT));
        modelTeapot->SetScale(0.01f);
        modelTeapot->SetPosition(glm::vec3(-3.0f, 0.0f, 0.0f));
        modelTeapot->SetRotation(glm::vec3(-0.2f, 0.8f, 0.35f));
        m_TestScene.AddOpaqueObject(modelTeapot);


        m_TerrainHeightMap = midori::Texture2D::Create(TEXTURE_TERRAIN_HEIGHTMAP);
        m_TerrainHeightMap->Bind(TEXTURE_TERRAIN_HEIGHTMAP_ID);
        m_TerrainColourMap = midori::Texture2D::Create(TEXTURE_TERRAIN_COLORMAP);
        m_TerrainColourMap->Bind(TEXTURE_TERRAIN_COLORMAP_ID);


        uint8_t shaders =
            (uint8_t) midori::ShaderProgramType::vertex |
            (uint8_t) midori::ShaderProgramType::fragment |
            (uint8_t) midori::ShaderProgramType::tessellation;
        m_TerrainShader = midori::Shader::Load(SHADER_TERRAIN, shaders);
        m_TerrainShader->Bind();
        m_TerrainShader->UploadUniformFloat("u_TerrainScale", CONF_TERRAIN_SCALE);
        m_TerrainShader->UploadUniformInt("u_DepthMap", TEXTURE_TERRAIN_HEIGHTMAP_ID);
        m_TerrainShader->UploadUniformInt("u_ColourMap", TEXTURE_TERRAIN_COLORMAP_ID);

        m_TerrainModel = midori::VertexArray::Create();

        const float halfWidth = CONF_TERRAIN_WIDTH * 0.5f;
        const float halfLength = CONF_TERRAIN_LENGTH * 0.5f;
        const float terrainHeight = -50.0f;

        const unsigned int Quad_Index_Count = 4;
        float terrainPlane[Quad_Index_Count * (3 + 2)] = {
            -halfWidth, terrainHeight, -halfLength,   0.0f, 1.0f,
            -halfWidth, terrainHeight,  halfLength,   0.0f, 0.0f,
             halfWidth, terrainHeight, -halfLength,   1.0f, 1.0f,
             halfWidth, terrainHeight,  halfLength,   1.0f, 0.0f
        };

        midori::ref<midori::VertexBuffer> terrainVB = midori::VertexBuffer::Create(terrainPlane, Quad_Index_Count * (3 + 2));
        terrainVB->SetLayout({
            {midori::ShaderDataType::Float3, "a_Position"},
            {midori::ShaderDataType::Float2, "a_TexCoord"}
        });
        m_TerrainModel->AddVertexBuffer(terrainVB);

        auto terrainObject = midori::make_ref<midori::SceneObject>();
        terrainObject->SetShader(m_TerrainShader);
        terrainObject->SetVertexArray(m_TerrainModel);
        terrainObject->SetGeometryPrimitive(midori::GeometryPrimitive::QuadPatches);
        m_TestScene.AddOpaqueObject(terrainObject);

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

    midori::ref<midori::Shader> m_MeshLoadShader;
    midori::ref<midori::VertexArray> m_TeapotModel;

    midori::ref<midori::Texture2D> m_TerrainHeightMap;
    midori::ref<midori::Texture2D> m_TerrainColourMap;
    midori::ref<midori::Shader> m_TerrainShader;
    midori::ref<midori::VertexArray> m_TerrainModel;
 
    midori::ref<midori::Texture2D> m_TextureCrate;
    midori::ref<midori::Texture2D> m_TextureFLogo;

    midori::Scene m_TestScene;

    midori::PerspectiveCamera* m_Camera;
    float m_MoveSpeed = 15.0f;
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
