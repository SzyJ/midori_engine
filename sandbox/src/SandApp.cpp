// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: SandApp.cpp
// Date: 09/10/2019

#include "Core.h"
#include <Midori.h>
#include "imgui/imgui.h"

#include <midori/renderer/MeshLoader.h>

#include <glm/gtx/string_cast.hpp>


class ExampleLayer : public midori::Layer {
public:
    ExampleLayer() : Layer("Test_Layer") {
        m_CursorEnabled = true;
        midori::Application::Get().GetWindow().SetCursorEnabled(m_CursorEnabled);

        unsigned int screenWidth = midori::Application::Get().GetWindow().GetWindowWidth();
        unsigned int screenHeight = midori::Application::Get().GetWindow().GetWindowHeight();

        m_Camera = new midori::PerspectiveCamera((float) screenWidth / (float) screenHeight, glm::vec3(0.0f, 5.0f, -10.0f));
        m_Camera->Rotate(180.0f, -15.0f);

        m_TestScene.SetCamera(m_Camera);

        m_TextureWhite = midori::Texture2D::Create(TEXTURE_WHITE);
        //m_TextureWhite->Bind(TEXTURE_WHITE_ID);

        m_TextureMetal = midori::Texture2D::Create(TEXTURE_METAL);
        //m_TextureMetal->Bind(TEXTURE_METAL_ID);

        m_MeshLoadShader = midori::Shader::Load(SHADER_MODEL_LOADER);
        m_MeshLoadShader->Bind();
        //m_MeshLoadShader->UploadUniformInt("u_Texture", TEXTURE_WHITE_ID);

        m_HelicopterShader = midori::Shader::Load(SHADER_MODEL_LOADER);
        m_HelicopterShader->Bind();
        //m_HelicopterShader->UploadUniformInt("u_Texture", TEXTURE_METAL_ID);


        unsigned int indexBuffer[6] = {
            0, 1, 2, 1, 2, 3
        };
        auto groundIB = midori::IndexBuffer::Create(indexBuffer, 6);

        const int bufferSize = 4 * (3 + 3 + 2);
        float vertexBuffer[bufferSize]{
            -1.0f,  0.0f, -1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
            -1.0f,  0.0f,  1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f,
             1.0f,  0.0f, -1.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
             1.0f,  0.0f,  1.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f
        };
        midori::ref<midori::VertexBuffer> groundVB = midori::VertexBuffer::Create(vertexBuffer, bufferSize);
        groundVB->SetLayout({
            {midori::ShaderDataType::Float3, "a_Position"},
            {midori::ShaderDataType::Float3, "a_Normal"},
            {midori::ShaderDataType::Float2, "a_TexCoord"}
            });

        auto groundVA = midori::VertexArray::Create();
        groundVA->AddVertexBuffer(groundVB);
        groundVA->SetIndexBuffer(groundIB);

        auto ground = midori::make_ref<midori::SceneObject>();
        ground->SetShader(m_MeshLoadShader);
        ground->SetVertexArray(groundVA);
        ground->SetPosition(glm::vec3(0.0f, -3.0f, 0.0f));
        ground->SetScale(75.0f);
        ground->SetMaterial(midori::Material::Chrome());

        m_TestScene.AddOpaqueObject(ground);

        auto testSquare = midori::make_ref<midori::SceneObject>();
        testSquare->SetShader(m_MeshLoadShader);
        testSquare->SetVertexArray(groundVA);
        testSquare->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
        testSquare->SetScale(1.0f);
        testSquare->SetRotation(glm::vec3(0.5f, 0.0f, 0.0f));
        testSquare->SetMaterial(midori::Material::Chrome());
        
        m_TestScene.AddOpaqueObject(testSquare);

        auto building = midori::make_ref<midori::SceneObject>();
        building->SetShader(m_MeshLoadShader);
        building->SetVertexArray(midori::MeshLoader::Load(MODEL_BUILDING));
        building->SetPosition(glm::vec3(0.0f, -3.0f, 7.5f));
        building->SetMaterial(midori::Material::WhiteRubber());

        m_TestScene.AddOpaqueObject(building);

        m_Helicopter = midori::make_ref<midori::SceneObject>();
        m_Helicopter->SetShader(m_HelicopterShader);
        m_Helicopter->SetVertexArray(midori::MeshLoader::Load(MODEL_HELICOPTER));
        m_Helicopter->SetScale(1.0f);
        m_Helicopter->SetPosition(glm::vec3(-3.0f, 0.0f, 0.0f));
        m_Helicopter->SetRotation(glm::vec3(-0.2f, 0.8f, 0.35f));
        m_Helicopter->SetMaterial(midori::Material::Silver());

        m_TestScene.AddOpaqueObject(m_Helicopter);

        //m_TerrainHeightMap = midori::Texture2D::Create(TEXTURE_TERRAIN_HEIGHTMAP);
        //m_TerrainHeightMap->Bind(TEXTURE_TERRAIN_HEIGHTMAP_ID);
        //m_TerrainColourMap = midori::Texture2D::Create(TEXTURE_TERRAIN_COLORMAP);
        //m_TerrainColourMap->Bind(TEXTURE_TERRAIN_COLORMAP_ID);

        //uint8_t shaders =
        //    (uint8_t) midori::ShaderProgramType::vertex |
        //    (uint8_t) midori::ShaderProgramType::fragment |
        //    (uint8_t) midori::ShaderProgramType::tessellation;
        //m_TerrainShader = midori::Shader::Load(SHADER_TERRAIN, shaders);
        //m_TerrainShader->Bind();
        //m_TerrainShader->UploadUniformFloat("u_TerrainScale", CONF_TERRAIN_SCALE);
        //m_TerrainShader->UploadUniformInt("u_DepthMap", TEXTURE_TERRAIN_HEIGHTMAP_ID);
        //m_TerrainShader->UploadUniformInt("u_ColourMap", TEXTURE_TERRAIN_COLORMAP_ID);

        //m_TerrainModel = midori::VertexArray::Create();

        //const float halfWidth = CONF_TERRAIN_WIDTH * 0.5f;
        //const float halfLength = CONF_TERRAIN_LENGTH * 0.5f;
        //const float terrainHeight = -50.0f;

        //const unsigned int Quad_Index_Count = 4;
        //float terrainPlane[Quad_Index_Count * (3 + 2)] = {
        //    -halfWidth, terrainHeight, -halfLength,   0.0f, 1.0f,
        //    -halfWidth, terrainHeight,  halfLength,   0.0f, 0.0f,
        //     halfWidth, terrainHeight, -halfLength,   1.0f, 1.0f,
        //     halfWidth, terrainHeight,  halfLength,   1.0f, 0.0f
        //};

        //midori::ref<midori::VertexBuffer> terrainVB = midori::VertexBuffer::Create(terrainPlane, Quad_Index_Count * (3 + 2));
        //terrainVB->SetLayout({
        //    {midori::ShaderDataType::Float3, "a_Position"},
        //    {midori::ShaderDataType::Float2, "a_TexCoord"}
        //});
        //m_TerrainModel->AddVertexBuffer(terrainVB);

        //auto terrainObject = midori::make_ref<midori::SceneObject>();
        //terrainObject->SetShader(m_TerrainShader);
        //terrainObject->SetVertexArray(m_TerrainModel);
        //terrainObject->SetGeometryPrimitive(midori::GeometryPrimitive::QuadPatches);
        //m_TestScene.AddOpaqueObject(terrainObject);


        m_TestScene.SetSkybox(midori::make_ref<midori::Skybox>(TEXTURE_SKYBOX));

        m_CenterLight = midori::make_ref<midori::PointLight>(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        m_SceneLight = midori::make_ref<midori::PointLight>(glm::vec3(-10.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        m_SceneLight1 = midori::make_ref<midori::PointLight>(glm::vec3(10.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        m_LightManager = midori::make_ref<midori::LightingManager>();
        m_LightManager->AddPointLight(m_SceneLight);
        m_LightManager->AddPointLight(m_SceneLight1);

        m_LightManager->AddDirectionalLight(midori::make_ref<midori::DirectionalLight>(glm::vec3(0.0f, 1.0f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));

        m_SpotLight = midori::make_ref<midori::SpotLight>();
        m_SpotLight->Position = glm::vec3(0.0f, 0.0f, 3.0f);
        m_SpotLight->Color = glm::vec3(1.0f, 1.0f, 1.0f);

        m_SpotLight1 = midori::make_ref<midori::SpotLight>();
        m_SpotLight1->Position = glm::vec3(0.0f, 0.0f, 15.0f);
        m_SpotLight1->Color = glm::vec3(1.0f, 0.0f, 1.0f);

        m_LightManager->AddSpotLight(m_SpotLight);
        m_LightManager->AddSpotLight(m_SpotLight1);

        m_TestScene.SetLightManager(m_LightManager);

        m_LightManager->UpdateFrameBufferSize(screenWidth, screenHeight);

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

        m_TotalTime += delta;

        //m_Helicopter->SetRotation(glm::vec3(-0.2f, glm::cos(m_TotalTime * 0.3f), glm::sin(m_TotalTime * 0.3f)));
        //m_SceneLight->SetPosition(glm::vec3(glm::sin(m_TotalTime) * m_FlightSpeed, 0.0f, glm::cos(m_TotalTime) * m_FlightSpeed));
        m_Helicopter->SetPosition(glm::vec3(glm::sin(m_TotalTime) * m_FlightSpeed, 0.0f, glm::cos(m_TotalTime) * -m_FlightSpeed));
        m_Helicopter->SetRotation(glm::vec3(0.0f, glm::cos(m_TotalTime * 0.3f), 0.0f));

        m_SpotLight->Direction = glm::vec3(glm::sin(m_TotalTime), -0.5f, 1.0f);
        m_SpotLight1->Direction = glm::vec3(glm::cos(m_TotalTime), -0.5f, -1.0f);

        //m_SpotLight->Position = glm::vec3(glm::sin(m_TotalTime) * m_FlightSpeed, 0.0f, glm::cos(m_TotalTime) * m_FlightSpeed);
        //m_SpotLight->Direction = glm::vec3(glm::sin(m_TotalTime), -0.5f, 1.0f);

        //m_SpotLight->Position = m_Camera->GetPosition();
        //m_SpotLight->Direction = m_Camera->GetDirection();


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


        m_TestScene.DrawDepth();

        midori::RenderCommand::SetClearColor({ 0.26f, 0.26f, 0.26f, 1.0f });
        midori::RenderCommand::Clear();

        m_TestScene.Draw();
    }

    void OnImGuiRender() override {
        ImGui::Begin("FPS");
        ImGui::Text(std::to_string((1.0f/m_DeltaAverage)).c_str());

        ImGui::Text(std::string("Cam Pos:").append(glm::to_string(m_Camera->GetDirection())).c_str());
        ImGui::Text(std::string("SpL Pos:").append(glm::to_string(m_SpotLight->Direction)).c_str());

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

    midori::ref<midori::LightingManager> m_LightManager;
    midori::ref<midori::PointLight> m_CenterLight;
    midori::ref<midori::PointLight> m_SceneLight;
    midori::ref<midori::PointLight> m_SceneLight1;

    midori::ref<midori::Shader> m_MeshLoadShader;
    
    midori::ref<midori::Texture2D> m_TerrainHeightMap;
    midori::ref<midori::Texture2D> m_TerrainColourMap;
    midori::ref<midori::Shader> m_TerrainShader;
    midori::ref<midori::VertexArray> m_TerrainModel;
 
    midori::ref<midori::Texture2D> m_TextureWhite;
    midori::ref<midori::Texture2D> m_TextureMetal;

    midori::ref<midori::Shader> m_HelicopterShader;
    midori::ref<midori::SceneObject> m_Helicopter;

    midori::ref<midori::SpotLight> m_SpotLight;
    midori::ref<midori::SpotLight> m_SpotLight1;

    midori::Scene m_TestScene;

    float m_TotalTime = 0.0f;

    float m_FlightSpeed = 5.0f;

    midori::PerspectiveCamera* m_Camera;
    float m_MoveSpeed = 10.0f;
    float m_LookSens = 0.1f;

    bool m_CursorEnabled = false;

    void OnWindowResize(midori::WindowResizeEvent& resizeEvent) {
        const auto newWidth = resizeEvent.GetWidth();
        const auto newHeight = resizeEvent.GetHeight();

        midori::RenderCommand::SetViewport(0, 0, newWidth, newHeight);
        m_Camera->OnWindowResize(newWidth, newHeight);
        m_LightManager->UpdateFrameBufferSize(newWidth, newHeight);
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
