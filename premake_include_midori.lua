-- Author: Szymon Jackiewicz
-- 
-- Project: midori_engine
-- File: premake_include_midori.lua
-- Date: 21/11/2019

-- Requires midori_path to be configured to the location of project folder relative to workspace location

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Midori Dependencies
midoriincludes = {}
midoriincludes["spdlog"]        = ("%{wks.location}/" .. midori_path .. "midori_engine/3rd_party/spdlog/include")
midoriincludes["glfw"]          = ("%{wks.location}/" .. midori_path .. "midori_engine/3rd_party/glfw/include")
midoriincludes["glad"]          = ("%{wks.location}/" .. midori_path .. "midori_engine/3rd_party/glad/include")
midoriincludes["imgui"]         = ("%{wks.location}/" .. midori_path .. "midori_engine/3rd_party/imgui")
midoriincludes["glm"]           = ("%{wks.location}/" .. midori_path .. "midori_engine/3rd_party/glm")
midoriincludes["stb_image"]     = ("%{wks.location}/" .. midori_path .. "midori_engine/3rd_party/stb_image")
midoriincludes["tinyobjloader"] = ("%{wks.location}/" .. midori_path .. "midori_engine/3rd_party/tinyobjloader")

-- 3rd Party Projects --
include "premake_projects/glfw.lua"
include "premake_projects/glad.lua"
include "premake_projects/imgui.lua"

-- Midori Engine --
-- Requires: glfw, glad, imgui
include "premake_projects/midori_engine.lua"
