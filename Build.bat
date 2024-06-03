@echo off
REM Run the premake5 executable
call Build\Premake\premake5.exe vs2022 --file="Solution.lua"

REM Pause the script to see the output
pause