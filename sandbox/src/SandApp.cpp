#include <Midori.h>

class TestLayer : public midori::Layer {
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
        
    }

    void OnEvent(midori::Event& event) override {
        MD_TRACE("Event in {0}: {1}", GetDebugName(), event);
    }
};

class Sandbox : public midori::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer());
    }

    ~Sandbox() {}
};

midori::Application* midori::CreateApplication() {
    return new Sandbox();
}
