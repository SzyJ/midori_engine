// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: Log.cpp
// Date: 02/10/2019

#include "mdpch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace midori {

    ref<spdlog::logger> Log::s_CoreLogger;

    ref<spdlog::logger> Log::s_AppLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("MIDORI");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_AppLogger = spdlog::stdout_color_mt("APP");
        s_AppLogger->set_level(spdlog::level::trace);
    }

}
