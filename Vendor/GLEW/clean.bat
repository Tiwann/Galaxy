

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

if exist GLEW.vcxproj del GLEW.vcxproj
if exist GLEW.vcxproj.user del GLEW.vcxproj.user
if exist GLEW.vcxproj.filters del GLEW.vcxproj.filters

echo Cleaned GLEW directory!


