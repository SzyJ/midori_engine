#pragma once

#include <memory>

#include "midori/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Midori {

    class MIDORI_API Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_AppLogger;
    };

}

// Core log macros
#define MD_CORE_TRACE(...)    ::Midori::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MD_CORE_INFO(...)     ::Midori::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MD_CORE_WARN(...)     ::Midori::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MD_CORE_ERROR(...)    ::Midori::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MD_CORE_FATAL(...)    ::Midori::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client app log macros
#define MD_TRACE(...)	      ::Midori::Log::GetAppLogger()->trace(__VA_ARGS__)
#define MD_INFO(...)	      ::Midori::Log::GetAppLogger()->info(__VA_ARGS__)
#define MD_WARN(...)	      ::Midori::Log::GetAppLogger()->warn(__VA_ARGS__)
#define MD_ERROR(...)	      ::Midori::Log::GetAppLogger()->error(__VA_ARGS__)
#define MD_FATAL(...)	      ::Midori::Log::GetAppLogger()->fatal(__VA_ARGS__)
