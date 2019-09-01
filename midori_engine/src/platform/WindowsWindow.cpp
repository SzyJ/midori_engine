#include "mdpch.h"
#include "WindowsWindow.h"

namespace Midori {

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
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enableVSync) {
        glfwSwapInterval(enableVSync ? 1 : 0);
        m_WindowData.VSync = enableVSync;
    }

    void WindowsWindow::Init(const WindowProperties& properties) {
        m_WindowData.Title = properties.Title;
        m_WindowData.Width = properties.Width;
        m_WindowData.Height = properties.Height;

        MD_CORE_INFO("Creating window: [{0}] ({1}, {2})", properties.Title, properties.Width, properties.Height);

        if (!s_GLFWInitialised) {
            // TODO: glfwTerminate on system shutdown
            int initSuccess = glfwInit();
            MD_CORE_ASSERT(initSuccess, "Failed to initialise GLFW");

            s_GLFWInitialised = true;
        }

        m_Window = glfwCreateWindow((int) properties.Width, (int) properties.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_WindowData);

        // TODO: Make configuarble
        SetVSync(true);
    }

    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
    }

}
