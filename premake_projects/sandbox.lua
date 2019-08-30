project "sandbox"
    location "%{wks.location}/sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/midori_engine/src",
        "%{midoriincludes.spdlog}"
    }

    links {
        "midori_engine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "MD_PLATFORM_WINDOWS"
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
