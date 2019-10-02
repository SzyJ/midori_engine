-- Author: Szymon Jackiewicz
-- 
-- Project: midori_engine
-- File: premake5.lua
-- Date: 02/10/2019

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
midoriincludes["imgui"]   = "%{wks.location}/midori_engine/3rd_party/imgui"

-- GLFW --
include "premake_projects/glfw.lua"
include "premake_projects/glad.lua"
include "premake_projects/imgui.lua"

-- Midori Engine --
-- Requires: glfw, glad, imgui
include "premake_projects/midori_engine.lua"

-- Sandbox App --
-- Requires: midori_engine
include "premake_projects/sandbox.lua"
