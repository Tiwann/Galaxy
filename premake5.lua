workspace "Galaxy"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }

    startproject "Galaxy"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Galaxy"
include "Vendor/GLFW"