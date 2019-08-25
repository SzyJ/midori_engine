#include <stdio.h>
#include <Midori.h>

class Sandbox : public Midori::Application {
public:
    Sandbox() {}
    ~Sandbox() {}
};


int main() {
	printf("Hello World from Sandbox!\n");

    Sandbox* sandbox = new Sandbox();

    sandbox->Run();

    delete sandbox;
}