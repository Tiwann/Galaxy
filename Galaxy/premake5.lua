project "Galaxy"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir("binaries/" .. outputdir .. "/%{prj.name}")
    objdir("intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "source/**.cpp",
        "source/**.h",
        "external/**.c",
        "external/**.cpp",
        "external/**.h",
        "external/**.hpp",
        "Assets/**"
    }

    includedirs {
        "source",
        "external/glm",
        "external/spdlog/include",
        "external/stb",
        "external/imgui/include",
        "../Vendor/GLFW/include",
        "../Vendor/GLEW/include",
    }

    links {
        "GLFW",
        "GLEW",
        "opengl32.lib"
    }

    defines {
        "GLEW_STATIC"
    }


    filter { "configurations:Debug" }
        buildoptions "/MTd"
        defines { "DEBUG", "SPDLOG_COMPILED_LIB" }
        runtime "Debug"
        symbols "on"

    filter { "configurations:Release" }
        buildoptions "/MT"
        defines { "NDEBUG", "SPDLOG_COMPILED_LIB" }
        runtime "Release"
        optimize "on"
