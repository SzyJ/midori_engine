// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: OpenGLContext.cpp
// Date: 10/10/2019

#include "mdpch.h"
#include "OpenGLContext.h"
#include <glad/glad.h>

namespace midori {

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int gladInitSuccess = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        MD_CORE_ASSERT(gladInitSuccess, "Failed to initialise Glad");

        MD_CORE_INFO("OpenGL Info:\n\tVendor: {0}\n\tRenderer: {1}\n\tVersion: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }

}
