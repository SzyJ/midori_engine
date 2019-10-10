// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: NetworkLayer.h
// Date: 09/10/2019

#pragma once
#include "midori/layers/Layer.h"

namespace midori {

    struct NetworkConfigs {

    };


    class NetworkLayer final : protected Layer {
    public:
        using MessageReceivedCallback = std::function<void(const char* message, const int byteLength)>;

        NetworkLayer();
        virtual ~NetworkLayer();

        virtual void SetOnMessageReceivedCallback(const MessageReceivedCallback& onMessageReceived) = 0;
        virtual int SendMessage(const char* message, const int byteLength) = 0;

        void SetConfigs();
    };
    
}
