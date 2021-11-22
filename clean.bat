@echo off

if exist binaries (
    echo Deleting binaries directory
    rmdir /s /q binaries
)

if exist intermediate (
    echo Deleting intermediate directory
    rmdir /s /q intermediate
)

if exist .vs (
    echo Deleting .vs directory
    rmdir /s /q .vs
)

if exist Galaxy.sln del Galaxy.sln
if exist Galaxy\Galaxy.vcxproj del Galaxy\Galaxy.vcxproj
if exist Galaxy\Galaxy.vcxproj.user del Galaxy\Galaxy.vcxproj.user
if exist Galaxy\Galaxy.vcxproj.filters del Galaxy\Galaxy.vcxproj.filters

if exist Vendor\GLFW\GLFW.vcxproj del Vendor\GLFW\GLFW.vcxproj
if exist Vendor\GLFW\GLFW.vcxproj.user del Vendor\GLFW\GLFW.vcxproj.user
if exist Vendor\GLFW\GLFW.vcxproj.filters del Vendor\GLFW\GLFW.vcxproj.filters

echo Cleaned project directory!

PAUSE
