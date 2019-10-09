-- Author: Szymon Jackiewicz
-- 
-- Project: midori_engine
-- File: sandbox.lua
-- Date: 09/10/2019

project "sandbox"
    location "%{wks.location}/sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/midori_engine/src",
        "%{wks.location}/midori_engine/3rd_Party",
        "%{midoriincludes.spdlog}",
        "%{midoriincludes.glm}"
    }

    links {
        "midori_engine"
    }

    filter "system:windows"
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
