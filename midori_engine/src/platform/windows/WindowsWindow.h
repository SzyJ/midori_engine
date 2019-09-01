#pragma once
#include "midori/Window.h"
#include <GLFW/glfw3.h>

namespace Midori {

    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        virtual void OnUpdate() override;

        virtual inline int GetWindowWidth() override;
        virtual inline int GetWindowHeight() override;

        virtual void SetEventCallback(const EventcallbackFn& callback) override;

        virtual void SetVSync(bool enableVSync) override;
        virtual bool IsVSyncEnabled() override;

    private:
        struct WindowData {
            EventcallbackFn m_EventCallback;
        };

        GLFWwindow& m_window;

        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    };

}
