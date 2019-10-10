// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: WindowsNetworking.cpp
// Date: 10/10/2019

#include "mdpch.h"
#include "WindowsNetworking.h"

namespace midori {

    WindowsNetworking::WindowsNetworking() {}


    WindowsNetworking::~WindowsNetworking() {}

    bool WindowsNetworking::Initialize() { }

    void WindowsNetworking::SetOnMessageReceivedCallback(const MessageReceivedCallback& onMessageReceived) { }

    int WindowsNetworking::SendMessage(const char* message, const int byteLength) { }

}
