// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: NetworkLayer.cpp
// Date: 09/10/2019

#include "mdpch.h"
#include "NetworkLayer.h"

namespace midori {

    NetworkLayer::NetworkLayer() { }

    NetworkLayer::~NetworkLayer() { }

    int NetworkLayer::SendMessage(const char * message, int byteLength) {
        return 0;
    }

    void NetworkLayer::OnAttach() { }

    void NetworkLayer::OnDetach() { }

    void NetworkLayer::OnUpdate() { }

    void NetworkLayer::OnEvent(Event& event) { }

}
