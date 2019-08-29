#pragma once

#ifdef MD_PLATFORM_WINDOWS
extern Midori::Application* Midori::CreateApplication();

int main(int argc, char** argv) {
    Midori::Log::Init();

    MD_CORE_INFO("Welcome to Midori!");

    auto app = Midori::CreateApplication();
    app->Run();
    delete app;
}

#endif // MD_PLATFORM_WINDOWS
