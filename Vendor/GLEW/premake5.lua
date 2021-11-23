project "GLEW"
    kind "StaticLib"
    language "C"

    targetdir ("binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "include/**.h",
        "src/**.c"
    }

    includedirs { "include" }

    defines {
        "GLEW_STATIC",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"