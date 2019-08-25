#include <stdio.h>
#include <Midori.h>

class Sandbox : public Midori::Application {
public:
    Sandbox() {}
    ~Sandbox() {}
};

Midori::Application* Midori::CreateApplication() {
    printf("Hello World from Sandbox!\n");
    return new Sandbox();
}