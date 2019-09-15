#pragma once
#include "midori/layers/Layer.h"
#include "midori/events/Event.h"

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
    };
}
