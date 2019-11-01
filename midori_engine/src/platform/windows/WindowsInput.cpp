// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: WindowsInput.cpp
// Date: 02/10/2019

#include "mdpch.h"
#include "WindowsInput.h"
#include "midori/core/Application.h"

#include <GLFW/glfw3.h>

namespace midori {

    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode) {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button) {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl() {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return {(float) xPos, (float) yPos};
    }

    float WindowsInput::GetMouseXImpl() {
        auto pos = GetMousePositionImpl();

        return pos.first;
    }

    float WindowsInput::GetMouseYImpl() {
        auto pos = GetMousePositionImpl();

        return pos.second;
    }

}
