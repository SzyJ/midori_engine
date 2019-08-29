workspace "midori_engine"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "sandbox"

local outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "midori_engine"
    location "midori_engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/3rd_party/spdlog/include"
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
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
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

project "sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "midori_engine/3rd_party/spdlog/include",
        "midori_engine/src"
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
