workspace "GalaxyRenderer"
    architecture "x64"
    startproject "Galaxy"
    configurations { "Debug", "Release" }
    flags "MultiProcessorCompile"
    require "cmake/cmake"
    require "clion/clion"

bindir = "Binaries/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"
intermediatedir = "Intermediate/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

newaction 
{
    trigger = "clean",
    description = "Clean all the generated files",
    
    onStart = function()
        print("Cleaning all the generated files...")
    end,

    execute = function()
        os.rmdir("Binaries")
        os.rmdir("Intermediate")
        os.rmdir(".vs")
        os.rmdir(".idea")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        os.remove("**.sln")
        os.remove("**.make")
        os.remove("**Makefile")
    end,

    onEnd = function()
        print("Done.")
    end
}
    
project "GalaxyRenderer"
    location "Galaxy"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    systemversion "latest"

    targetdir (bindir)
    objdir (intermediatedir)

    files
    {
       "%{prj.location}/Source/*.cpp",
       "%{prj.location}/Source/*.h",
       "%{prj.location}/External/**.c",
       "%{prj.location}/External/**.cpp",
       "%{prj.location}/External/**.h",
       "%{prj.location}/External/**.hpp",
       "%{prj.location}/Assets/**",
    }

    includedirs
    {
        "GLFW/include",
        "GLAD/include",
        "%{prj.location}/External/glm",
        "%{prj.location}/External/spdlog/include",
        "%{prj.location}/External/stb",
        "%{prj.location}/External/imgui/include",
        "%{prj.location}/External/tinyfiledialogs"
    }

    defines
    {
        "GLFW_INCLUDE_NONE",
        "SPDLOG_COMPILED_LIB"
    }

    links
    {
        "GLAD",
        "GLFW",
    }

    filter "system:windows"
        links "opengl32"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        defines "DEBUG"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "GLFW"
    location "GLFW"
    kind "StaticLib"
    language "C"

    targetdir (bindir)
    objdir (intermediatedir)

    files
	{
	    "%{prj.location}/include/GLFW/glfw3.h",
        "%{prj.location}/include/GLFW/glfw3native.h",
        "%{prj.location}/src/internal.h",
        "%{prj.location}/src/platform.h",
        "%{prj.location}/src/mappings.h",
        "%{prj.location}/src/mappings.h.in",
        "%{prj.location}/src/context.c",
        "%{prj.location}/src/init.c",
        "%{prj.location}/src/input.c",
        "%{prj.location}/src/monitor.c",
        "%{prj.location}/src/platform.c",
        "%{prj.location}/src/platform.h",
        "%{prj.location}/src/vulkan.c",
        "%{prj.location}/src/window.c",
        "%{prj.location}/src/egl_context.c",
        "%{prj.location}/src/osmesa_context.c",
        "%{prj.location}/src/null_platform.h",
        "%{prj.location}/src/null_joystick.h",
        "%{prj.location}/src/null_init.c",
        
        "%{prj.location}/src/null_monitor.c",
        "%{prj.location}/src/null_window.c",
        "%{prj.location}/src/null_joystick.c",
	}

    includedirs "%{prj.location}/include"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
		    "%{prj.location}/src/win32_init.c",
            "%{prj.location}/src/win32_module.c",
            "%{prj.location}/src/win32_joystick.c",
            "%{prj.location}/src/win32_joystick.h",
            "%{prj.location}/src/win32_platform.h",
            "%{prj.location}/src/win32_monitor.c",
            "%{prj.location}/src/win32_time.h",
            "%{prj.location}/src/win32_time.c",
            "%{prj.location}/src/win32_thread.h",
            "%{prj.location}/src/win32_thread.c",
            "%{prj.location}/src/win32_window.c",
            "%{prj.location}/src/wgl_context.c",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
    
    filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"%{prj.location}/src/x11_init.c",
			"%{prj.location}/src/x11_monitor.c",
			"%{prj.location}/src/x11_window.c",
			"%{prj.location}/src/xkb_unicode.c",
			"%{prj.location}/src/posix_time.c",
			"%{prj.location}/src/posix_time.h",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/posix_thread.h",
			"%{prj.location}/src/posix_module.c",
			"%{prj.location}/src/posix_poll.c",
			"%{prj.location}/src/posix_poll.h",
			"%{prj.location}/src/glx_context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/osmesa_context.c",
			"%{prj.location}/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}


project "GLAD"
    location "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    systemversion "latest"

    targetdir (bindir)
    objdir (intermediatedir)

    files
    {
        "%{prj.location}/include/glad/glad.h",
        "%{prj.location}/include/KHR/khrplatform.h",
        "%{prj.location}/src/glad.c"
    }

    includedirs
    {
        "%{prj.location}/include"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
