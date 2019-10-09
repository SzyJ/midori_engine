// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: SandApp.cpp
// Date: 09/10/2019

#include <Midori.h>
#include "imgui/imgui.h"

class TestLayer : public midori::Layer {
public:
    TestLayer() : Layer("Test_Layer") {}

    void OnAttach() override {
        MD_INFO("Test Layer Attached");
    }

    void OnDetach() override {
        MD_INFO("Test Layer Detached");
    }

    void OnUpdate() override {
        if (midori::Input::IsKeyPressed(MD_KEY_TAB)) {
            MD_TRACE("Tab key is pressed!");
        }
    }

    void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }

    void OnEvent(midori::Event& event) override {
        if (event.GetEventType() == midori::EventType::KeyPressed) {

            midori::KeyPressedEvent& e = (midori::KeyPressedEvent&) event;

            if (e.GetKeyCode() == MD_KEY_TAB) {
                MD_TRACE("Tab key is pressed (event)!");
            }

            MD_TRACE("{0}", e.GetKeyCode());

        }
    }
};

class Sandbox : public midori::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer());
    }

    ~Sandbox() {}
};

midori::Application* midori::CreateApplication() { return new Sandbox(); }
