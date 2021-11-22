
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

if exist Galaxy.vcxproj del Galaxy.vcxproj
if exist Galaxy.vcxproj.user del Galaxy.vcxproj.user
if exist Galaxy.vcxproj.filters del Galaxy.vcxproj.filters

echo Cleaned Galaxy directory!




