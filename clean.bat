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
if exist GalaxyRenderer\GalaxyRenderer.vcxproj del GalaxyRenderer\GalaxyRenderer.vcxproj
if exist GalaxyRenderer\GalaxyRenderer.vcxproj.user del GalaxyRenderer\GalaxyRenderer.vcxproj.user
if exist GalaxyRenderer\GalaxyRenderer.vcxproj.filters del GalaxyRenderer\GalaxyRenderer.vcxproj.filters

echo Cleaned project directory!

PAUSE
