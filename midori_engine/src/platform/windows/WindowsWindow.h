#pragma once
#include "midori/Window.h"
#include <GLFW/glfw3.h>

namespace midori {

    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProperties& properties);
        virtual ~WindowsWindow();

        virtual void OnUpdate() override;

        virtual inline int GetWindowWidth() const override { return m_WindowData.properties.Width; }

        virtual inline int GetWindowHeight() const override { return m_WindowData.properties.Height; }

        virtual void SetEventCallback(const EventCallbackFn& callback) override {
            m_WindowData.EventCallback = callback;
        }

        virtual void SetVSync(bool enableVSync) override;

        virtual bool IsVSyncEnabled() const override { return m_WindowData.VSync; }

    private:
        struct WindowData {
            WindowProperties properties;

            bool VSync;

            EventCallbackFn EventCallback;
        };

        static bool s_GLFWInitialised;

        WindowData m_WindowData;

        GLFWwindow* m_Window;

        virtual void Init(const WindowProperties& props);
        virtual void Shutdown();
        inline void CreateGLFWWindow();
        inline void SetGLFWConfigurations();
        inline void SetGLFWCallbacks() const;

    };

}
