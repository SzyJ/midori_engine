// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Layer.h
// Date: 03/10/2019

#pragma once

#include "midori/Core.h"
#include "midori/events/Event.h"

#include "midori/core/DeltaTime.h"

namespace midori {

    class MIDORI_API Layer {
    public:
        Layer(std::string debugName = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}

        virtual void OnDetach() {}

        virtual void OnUpdate(DeltaTime delta) {}

        virtual void OnImGuiRender() {}

        virtual void OnEvent(Event& event) {}

        inline const std::string& GetDebugName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };

}
