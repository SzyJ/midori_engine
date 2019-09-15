#pragma once

#include "midori/Core.h"
#include "midori/events/Event.h"

namespace midori {

    class MIDORI_API Layer {
    public:
        Layer(std::string debugName = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetDebugName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };
    
}
