#include <Midori.h>

class TestLayer : public Midori::Layer {
public:
    TestLayer()
        : Layer("Test_Layer") {}

    void OnAttach() override {
        MD_INFO("Test Layer Attached");
    }

    void OnDetach() override {
        MD_INFO("Test Layer Detached");
    }

    void OnUpdate() override {  
        MD_INFO("Update to {0}", GetDebugName());
    }

    void OnEvent(Midori::Event& event) override {
        MD_TRACE("Event in {0}: {1}", GetDebugName(), event);
    }
};

class Sandbox : public Midori::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer());
    }

    ~Sandbox() {}
};

Midori::Application* Midori::CreateApplication() {
    return new Sandbox();
}
