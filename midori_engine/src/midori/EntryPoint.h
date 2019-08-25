#pragma once

#ifdef MD_PLATFORM_WINDOWS

#include "Application.h"

extern Midori::Application* Midori::CreateApplication();

int main(int argc, char** argv) {
    auto app = Midori::CreateApplication();
    app->Run();
    delete app;
}

#endif // MD_PLATFORM_WINDOWS
