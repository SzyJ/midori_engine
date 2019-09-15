#pragma once

#include "midori/Core.h"
#include "midori/layers/Layer.h"

namespace midori {

    //typedef std::vector<midori::Layer*> Layers;
    //typedef std::vector<midori::Layer*>::iterator LayerPtr;

    class MIDORI_API LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };

}