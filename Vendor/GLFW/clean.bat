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

echo Cleaned project directory!

PAUSE
