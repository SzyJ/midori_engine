// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: EntryPoint.h
// Date: 02/10/2019

#pragma once

#ifdef MD_PLATFORM_WINDOWS
extern midori::Application* midori::CreateApplication();

int main(int argc, char** argv) {
    midori::Log::Init();

    MD_CORE_INFO("Welcome to Midori!");

    auto app = midori::CreateApplication();
    app->Run();
    delete app;
}

#endif // MD_PLATFORM_WINDOWS
