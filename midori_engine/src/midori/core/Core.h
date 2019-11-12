// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Core.h
// Date: 09/10/2019

#pragma once

#include <memory>

#ifdef MD_PLATFORM_WINDOWS

#define MD_DEFAULT_RESOURCES "../midori_engine/res/"

#ifdef MD_CONFIG_DLL

    #ifdef MD_BUILD_DLL
        #define MIDORI_API __declspec(dllexport)
    #else
        #define MIDORI_API __declspec(dllimport)
    #endif // MD_BUILD_DLL

#else

    #define MIDORI_API 

#endif

#else

    #error Midori Engine currently only supports Windows

#endif // MD_PLATFORM_WINDOWS

#ifdef MD_DEBUG
    #define MD_ENABLE_ASSERTS
#endif // MD_DEBUG

#ifdef MD_ENABLE_ASSERTS
    #define MD_ASSERT(x, ...) { if(!(x)) { MD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define MD_CORE_ASSERT(x, ...) { if(!(x)) { MD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define MD_ASSERT(x, ...)
    #define MD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define MD_BIND_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

namespace midori {

    template<typename T>
    using scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr scope<T> make_scope(Args&& ... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr ref<T> make_ref(Args&& ... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}
