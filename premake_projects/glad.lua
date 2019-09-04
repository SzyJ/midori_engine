project "glad"
    location "%{wks.location}/midori_engine/3rd_party/glad"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/include/glad/glad.h",
        "%{prj.location}/include/KHR/khrplatform.h",
        "%{prj.location}/src/glad.c"
    }

    includedirs {
        "%{prj.location}/include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT" 
