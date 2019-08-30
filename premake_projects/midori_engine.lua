project "midori_engine"
    location "%{wks.location}/midori_engine"
    kind "SharedLib"
    language "C++"

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
        "%{midoriincludes.spdlog}"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "MD_PLATFORM_WINDOWS",
            "MD_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/" .. outputdir .. "/sandbox")
        }
        
    filter "configurations:Debug"
        defines "MD_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "MD_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "MD_DIST"
        optimize "On"
