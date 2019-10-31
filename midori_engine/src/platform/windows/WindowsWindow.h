// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: WindowsWindow.h
// Date: 02/10/2019

#pragma once
#include "midori/Window.h"
#include <GLFW/glfw3.h>
#include "platform/opengl/OpenGLContext.h"

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

        virtual void SetCursorEnabled(bool isEnabled) override;

        virtual inline void* GetNativeWindow() const override { return m_Window; }

    private:
        struct WindowData {
            WindowProperties properties;

            bool VSync;
            bool firstMouseSample = true;
            double lastMouseX;
            double lastMouseY;

            EventCallbackFn EventCallback;
        };

        static bool s_GLFWInitialised;

        WindowData m_WindowData;

        GLFWwindow* m_Window;
        GraphicsContext* m_GraphicsContext;

        virtual void Init(const WindowProperties& props);
        virtual void Shutdown();
        inline void CreateGLFWWindow();
        inline void SetGLFWConfigurations();
        inline void SetGLFWCallbacks() const;

    };

}
