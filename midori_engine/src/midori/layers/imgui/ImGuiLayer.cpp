#include "mdpch.h"
#include "ImGuiLayer.h"
#include <GLFW/glfw3.h>
#include "midori/Application.h"
#include "platform/opengl/ImGuiOpenGLRenderer.h"
#include <glad/glad.h>

namespace midori {

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();

        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // TODO: Change the keymap to use MIDORI key codes
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() {}

    void ImGuiLayer::OnUpdate() {
        Application& app = Application::Get();
        ImGuiIO& io = ImGui::GetIO();

        ImGui_ImplOpenGL3_NewFrame();

        io.DisplaySize = ImVec2(app.GetWindow().GetWindowWidth(), app.GetWindow().GetWindowHeight());
        float time = (float) glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : 1.0f / 60.0f;
        m_Time = time;

        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& event) {
        MD_CORE_WARN("IMGUI Event: {0}", event);

        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(MD_BIND_FUNCTION(ImGuiLayer::KeyPressedCallback));
        dispatcher.Dispatch<KeyReleasedEvent>(MD_BIND_FUNCTION(ImGuiLayer::KeyReleasedCallback));
        dispatcher.Dispatch<MouseMovedEvent>(MD_BIND_FUNCTION(ImGuiLayer::MouseMovedCallback));
        dispatcher.Dispatch<MouseScrolledEvent>(MD_BIND_FUNCTION(ImGuiLayer::MouseScrollCallback));
        dispatcher.Dispatch<MouseButtonPressedEvent>(MD_BIND_FUNCTION(ImGuiLayer::MouseButtonPressedCallback));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(MD_BIND_FUNCTION(ImGuiLayer::MouseButtonReleasedCallback));
    }

    bool ImGuiLayer::KeyPressedCallback(KeyPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeySuper= io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::KeyReleasedCallback(KeyReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::MouseMovedCallback(MouseMovedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(event.GetX(), event.GetY());

        return false;
    }

    bool ImGuiLayer::MouseScrollCallback(MouseScrolledEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += event.GetYOffset();
        io.MouseWheelH += event.GetXOffset();

        return false;
    }

    bool ImGuiLayer::MouseButtonPressedCallback(MouseButtonPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseDown[event.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::MouseButtonReleasedCallback(MouseButtonReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseDown[event.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::WindowResizeCallback(WindowResizeEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

        glViewport(0, 0, event.GetWidth(), event.GetHeight());
        return false;
    }

    bool ImGuiLayer::KeyTypedCallback(KeyTypedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        const int charCode = event.GetKeyCode();

        if (charCode > 0 && charCode < 0x10000) {
            io.AddInputCharacter((unsigned short) charCode);
        }

        return false;
    }

}
