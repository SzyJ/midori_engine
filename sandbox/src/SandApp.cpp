#include <Midori.h>

class Sandbox : public Midori::Application {
public:
    Sandbox() {}
    ~Sandbox() {}
};

Midori::Application* Midori::CreateApplication() {
    return new Sandbox();
}
