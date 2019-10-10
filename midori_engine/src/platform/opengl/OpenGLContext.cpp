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
        MD_ASSERT(gladInitSuccess, "Failed to initialise Glad");
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }

}
