

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

if exist GLFW.vcxproj del GLFW.vcxproj
if exist GLFW.vcxproj.user del GLFW.vcxproj.user
if exist GLFW.vcxproj.filters del GLFW.vcxproj.filters

echo Cleaned GLFW directory!


