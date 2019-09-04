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
midoriincludes["glfw"]   = "%{wks.location}/midori_engine/3rd_party/glfw/include"
midoriincludes["glad"]   = "%{wks.location}/midori_engine/3rd_party/glad/include"

-- GLFW --
include "premake_projects/glfw.lua"
include "premake_projects/glad.lua"

-- Midori Engine --
-- Requires: glfw, glad
include "premake_projects/midori_engine.lua"

-- Sandbox App --
-- Requires: midori_engine
include "premake_projects/sandbox.lua"
