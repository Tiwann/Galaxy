@echo off

if exist Galaxy.sln del Galaxy.sln

echo Deleted Galaxy solution!

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
