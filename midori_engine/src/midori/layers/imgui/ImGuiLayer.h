// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: ImGuiLayer.h
// Date: 02/10/2019

#pragma once
#include "midori/layers/Layer.h"
#include "midori/events/Event.h"
#include "midori/events/ApplicationEvent.h"
#include "midori/events/KeyEvent.h"
#include "midori/events/MouseEvent.h"

namespace midori {

    class MIDORI_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer() : Layer("IMGui_Layer") {}

        ~ImGuiLayer() {}

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;

    private:
        float m_Time = 0.0f;

        bool KeyPressedCallback(KeyPressedEvent& event);
        bool KeyReleasedCallback(KeyReleasedEvent& event);
        bool MouseMovedCallback(MouseMovedEvent& event);
        bool MouseScrollCallback(MouseScrolledEvent& event);
        bool MouseButtonPressedCallback(MouseButtonPressedEvent& event);
        bool MouseButtonReleasedCallback(MouseButtonReleasedEvent& event);
        bool WindowResizeCallback(WindowResizeEvent& event);
        bool KeyTypedCallback(KeyTypedEvent& event);
    };

}
