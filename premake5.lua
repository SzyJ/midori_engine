workspace "midori_engine"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Midori Dependencies
midoriincludes = {}
midoriincludes["spdlog"] = "%{wks.location}/midori_engine/3rd_party/spdlog/include"

-- Midori Engine --
-- Requires: glfw
include "premake_projects/midori_engine.lua"

-- Sandbox App --
-- Requires: midori_engine
include "premake_projects/sandbox.lua"
