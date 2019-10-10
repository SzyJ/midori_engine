-- Author: Szymon Jackiewicz
-- 
-- Project: midori_engine
-- File: midori_engine.lua
-- Date: 09/10/2019

project "midori_engine"
    location "%{wks.location}/midori_engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "mdpch.h"
    pchsource "%{prj.location}/src/mdpch.cpp"

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/3rd_Party/glm/glm/**.hpp",
        "%{prj.location}/3rd_Party/glm/glm/**.inl"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "MD_USE_NETWORKING"
    }

    includedirs {
        "%{prj.location}/src",
        "%{midoriincludes.spdlog}",
        "%{midoriincludes.glfw}",
        "%{midoriincludes.glad}",
        "%{midoriincludes.imgui}",
        "%{midoriincludes.glm}"
    }
    
    links { 
        "glfw",
        "glad",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "MD_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "MD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "MD_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "MD_DIST"
        runtime "Release"
        optimize "On"
