// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Log.h
// Date: 02/10/2019

#pragma once

#include "midori/core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace midori {

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
#define MD_CORE_TRACE(...)    ::midori::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MD_CORE_INFO(...)     ::midori::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MD_CORE_WARN(...)     ::midori::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MD_CORE_ERROR(...)    ::midori::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MD_CORE_FATAL(...)    ::midori::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client app log macros
#define MD_TRACE(...)	      ::midori::Log::GetAppLogger()->trace(__VA_ARGS__)
#define MD_INFO(...)	      ::midori::Log::GetAppLogger()->info(__VA_ARGS__)
#define MD_WARN(...)	      ::midori::Log::GetAppLogger()->warn(__VA_ARGS__)
#define MD_ERROR(...)	      ::midori::Log::GetAppLogger()->error(__VA_ARGS__)
#define MD_FATAL(...)	      ::midori::Log::GetAppLogger()->fatal(__VA_ARGS__)
