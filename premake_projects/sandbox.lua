-- Author: Szymon Jackiewicz
-- 
-- Project: midori_engine
-- File: sandbox.lua
-- Date: 02/10/2019

project "sandbox"
    location "%{wks.location}/sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/midori_engine/src",
        "%{midoriincludes.spdlog}",
        "%{midoriincludes.glm}"
    }

    links {
        "midori_engine"
    }

    filter "system:windows"
        cppdialect "C++17"
        
        systemversion "latest"

        defines {
            "MD_PLATFORM_WINDOWS"
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
