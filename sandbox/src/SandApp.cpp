// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: SandApp.cpp
// Date: 02/10/2019

#include <Midori.h>

class TestLayer : public midori::Layer {
public:
    TestLayer() : Layer("Test_Layer") {}

    void OnAttach() override {
        MD_INFO("Test Layer Attached");
    }

    void OnDetach() override {
        MD_INFO("Test Layer Detached");
    }

    void OnUpdate() override {}

    void OnEvent(midori::Event& event) override {
        if (event.GetEventType() == midori::EventType::KeyPressed) {

            midori::KeyPressedEvent& e = (midori::KeyPressedEvent&) event;

            if (e.GetKeyCode() == MD_KEY_TAB) {
                MD_TRACE("Tab key is pressed (event)!");
            }

            MD_TRACE("{0}", (char)e.GetKeyCode());

        }
    }
};

class Sandbox : public midori::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer());
        PushOverlay(new midori::ImGuiLayer());
    }

    ~Sandbox() {}
};

midori::Application* midori::CreateApplication() { return new Sandbox(); }
