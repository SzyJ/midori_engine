#include "mdpch.h"
#include "LayerStack.h"

namespace midori {

    LayerStack::LayerStack() = default;

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, layer);
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(Layer* overlay) {
        m_Layers.emplace_back(overlay);
        overlay->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer) {
        const auto layerIndex = std::find(m_Layers.begin(), m_Layers.end(), layer);

        if (layerIndex != m_Layers.end()) {
            m_Layers.erase(layerIndex);
            layer->OnDetach();
            --m_LayerInsertIndex;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay) {
        const auto overlayIndex = std::find(m_Layers.begin(), m_Layers.end(), overlay);

        if (overlayIndex != m_Layers.end()) {
            m_Layers.erase(overlayIndex);
            overlay->OnDetach();
        }
    }

}
