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

#ifdef MD_ENABLE_ASSERTS
    #define MD_ASSERT(x, ...) { if(!(x)) { MD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define MD_CORE_ASSERT(x, ...) { if(!(x)) { MD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define MD_ASSERT(x, ...)
    #define MD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
