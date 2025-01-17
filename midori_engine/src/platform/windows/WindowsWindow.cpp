// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: WindowsWindow.cpp
// Date: 31/10/2019

#include "mdpch.h"
#include "WindowsWindow.h"
#include "midori/events/ApplicationEvent.h"
#include "midori/events/KeyEvent.h"
#include "midori/events/MouseEvent.h"

namespace midori {

    Window* Window::Create(const WindowProperties& props) {
        return new WindowsWindow(props);
    }

    bool WindowsWindow::s_GLFWInitialised = false;

    WindowsWindow::WindowsWindow(const WindowProperties& props) {
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        Shutdown();
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        m_GraphicsContext->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enableVSync) {
        glfwSwapInterval(enableVSync ? 1 : 0);
        m_WindowData.VSync = enableVSync;
    }

    void WindowsWindow::SetCursorEnabled(bool isEnabled) {
        glfwSetInputMode(m_Window, GLFW_CURSOR, isEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }

    void WindowsWindow::Init(const WindowProperties& properties) {
        m_WindowData.properties = WindowProperties(properties);

        MD_CORE_INFO("Creating window: [{0}] ({1}, {2})", properties.Title, properties.Width, properties.Height);

        if (!s_GLFWInitialised) {
            // TODO: glfwTerminate on system shutdown
            int initSuccess = glfwInit();
            MD_CORE_ASSERT(initSuccess, "Failed to initialise GLFW");
            s_GLFWInitialised = true;
        }

        CreateGLFWWindow();
        SetGLFWConfigurations();
        SetGLFWCallbacks();
    }

    void WindowsWindow::CreateGLFWWindow() {
        m_Window = glfwCreateWindow((int) m_WindowData.properties.Width, (int) m_WindowData.properties.Height, m_WindowData.properties.Title.c_str(), nullptr, nullptr);


        m_GraphicsContext = new OpenGLContext(m_Window);
        m_GraphicsContext->Init();

        glfwSetWindowUserPointer(m_Window, &m_WindowData);
    }

    void WindowsWindow::SetGLFWConfigurations() {
        // TODO: Make configurable

        SetVSync(true);
    }

    void WindowsWindow::SetGLFWCallbacks() const {
        // Error Callback
        glfwSetErrorCallback([](int error, const char* description) {
            MD_CORE_ERROR("GLFW Error [{0}]: {1}", error, description);
        });

        // Window Resize Callback
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.properties.Width = width;
            data.properties.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        // Window Close Callback
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        // Keypress Callback
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
            }
            break;
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
            }
            break;
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
            }
            break;
            default: break;
            }
        });

        // Key Typed
        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int charCode) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            KeyTypedEvent event(charCode);
            data.EventCallback(event);
        });

        // Mouse Button Callback
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
            }
            break;
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
            }
            break;
            default: break;
            }
        });

        // Mouse Scroll Callback
        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float) xOffset, (float) yOffset);
            data.EventCallback(event);
        });

        // Cursor Move Callback
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            if (data.firstMouseSample) {
                data.lastMouseX = xPos;
                data.lastMouseY = yPos;
                data.firstMouseSample = false;
            }

            MouseMovedEvent event( -1.0f * (float) (data.lastMouseX - xPos), (float) (data.lastMouseY - yPos));
            data.lastMouseX = xPos;
            data.lastMouseY = yPos;
            data.EventCallback(event);
        });

        glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.firstMouseSample = true;
        });
    }

    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
    }

}
