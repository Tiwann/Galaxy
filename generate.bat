@echo off
call Vendor\Premake5\premake5.exe vs2022
if exist Galaxy.sln echo Successfully generated vs2022 solution !

PAUSE