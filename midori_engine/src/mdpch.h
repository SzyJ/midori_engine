// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: mdpch.h
// Date: 09/10/2019

#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "midori/Log.h"

#ifdef MD_PLATFORM_WINDOWS
    #include <Windows.h>

    #ifdef MD_USE_NETWORKING
        #include <winsock2.h>
        #include <Ws2tcpip.h>
    #endif

#else

    /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
    #ifdef MD_USE_NETWORKING
        #include <sys/socket.h>
        #include <arpa/inet.h>
        #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
        #include <unistd.h> /* Needed for close() */
    #endif

#endif // MD_PLATFORM_WINDOWS
