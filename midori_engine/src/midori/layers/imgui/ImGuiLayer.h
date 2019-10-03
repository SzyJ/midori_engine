// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: ImGuiLayer.h
// Date: 03/10/2019

#pragma once
#include "midori/layers/Layer.h"

#include "midori/layers/imgui/ImGuiLayer.h"

namespace midori {

    class MIDORI_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer() : Layer("ImGui_Layer") {}

        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    };

}
