project "Galaxy"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir("../binaries/" .. outputdir .. "/%{prj.name}")
    objdir("../intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "source/**.cpp",
        "source/**.h",
        "external/**.c",
        "external/**.cpp",
        "external/**.h",
        "external/**.hpp"
    }

    includedirs {
        "source",
        "external/glm",
        "external/spdlog",
        "../Vendor/GLFW/include",
    }

    links {
        "GLFW"
    }


    filter { "configurations:Debug" }
        buildoptions "/MTd"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter { "configurations:Release" }
        buildoptions "/MT"
        defines "NDEBUG"
        runtime "Release"
        optimize "on"
