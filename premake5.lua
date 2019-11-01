-- Author: Szymon Jackiewicz
-- 
-- Project: midori_engine
-- File: premake5.lua
-- Date: 01/11/2019

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
midoriincludes["spdlog"]    = "%{wks.location}/midori_engine/3rd_party/spdlog/include"
midoriincludes["glfw"]      = "%{wks.location}/midori_engine/3rd_party/glfw/include"
midoriincludes["glad"]      = "%{wks.location}/midori_engine/3rd_party/glad/include"
midoriincludes["imgui"]     = "%{wks.location}/midori_engine/3rd_party/imgui"
midoriincludes["glm"]       = "%{wks.location}/midori_engine/3rd_party/glm"
midoriincludes["stb_image"] = "%{wks.location}/midori_engine/3rd_party/stb_image"

-- 3rd Party Projects --
include "premake_projects/glfw.lua"
include "premake_projects/glad.lua"
include "premake_projects/imgui.lua"

-- Midori Engine --
-- Requires: glfw, glad, imgui
include "premake_projects/midori_engine.lua"

-- Sandbox App --
-- Requires: midori_engine
include "premake_projects/sandbox.lua"
