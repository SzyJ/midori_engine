#pragma once

#ifdef MD_PLATFORM_WINDOWS

    #ifdef MD_BUILD_DLL
        #define MIDORI_API __declspec(dllexport)
    #else
        #define MIDORI_API __declspec(dllimport)
    #endif // MD_BUILD_DLL

#else

    #error Midori Engine currently only supports Windows

#endif // MD_PLATFORM_WINDOWS
