@echo off

if exist Galaxy.sln del Galaxy.sln
echo Deleted Galaxy solution!

if exist .idea (
    echo Deleting JetBrains files
    rmdir /s /q .idea
)

if exist .vs (
    echo Deleting Visual Studio files
    rmdir /s /q .vs
)


cd Galaxy
call clean.bat
cd ..\

cd Vendor/GLFW
call clean.bat
cd ..\..\

cd Vendor/GLEW
call clean.bat
cd ..\..\

PAUSE
