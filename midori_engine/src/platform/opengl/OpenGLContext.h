// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLContext.h
// Date: 10/10/2019

#pragma once
#include "midori/renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace midori {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* window)
            : m_WindowHandle(window) {
            MD_CORE_ASSERT(m_WindowHandle, "Window handle is null!")
        }
        OpenGLContext() = delete;
        ~OpenGLContext();

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };

}
