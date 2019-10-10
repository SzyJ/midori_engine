// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: WindowsNetworking.h
// Date: 10/10/2019

#pragma once
#include "midori/networking/Networking.h"

namespace midori {

    class WindowsNetworking : public Networking {
    public:
        WindowsNetworking();
        ~WindowsNetworking();


        virtual bool Initialize() override;
        virtual void SetOnMessageReceivedCallback(const MessageReceivedCallback& onMessageReceived) override;
        virtual int SendMessage(const char* message, const int byteLength) override;
    };

}
