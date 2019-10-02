-- Author: Szymon Jackiewicz
-- 
-- Project: midori_engine
-- File: midori_engine.lua
-- Date: 02/10/2019

project "midori_engine"
    location "%{wks.location}/midori_engine"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "mdpch.h"
    pchsource "%{prj.location}/src/mdpch.cpp"

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/src",
        "%{midoriincludes.spdlog}",
        "%{midoriincludes.glfw}",
        "%{midoriincludes.glad}",
        "%{midoriincludes.imgui}"
    }
    
    links { 
        "glfw",
        "glad",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        
        systemversion "latest"

        defines {
            "MD_PLATFORM_WINDOWS",
            "MD_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/" .. outputdir .. "/sandbox")
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
