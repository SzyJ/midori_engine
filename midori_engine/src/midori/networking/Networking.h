// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Networking.h
// Date: 10/10/2019

#pragma once

namespace midori {

    class Networking {
    public:
        using MessageReceivedCallback = std::function<void(const char* message, const int byteLength)>;

        Networking();
        virtual ~Networking();

        virtual bool Initialize() = 0;
        virtual void SetOnMessageReceivedCallback(const MessageReceivedCallback& onMessageReceived) = 0;
        virtual int SendMessage(const char* message, const int byteLength) = 0;
    };

}
