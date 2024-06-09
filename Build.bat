@echo off

REM Delete Binaries, Intermediate, .vs, and .idea directories
for /d /r %%d in (Binaries Intermediate .vs .idea) do if exist "%%d" (
    echo Deleting directory %%d
    rmdir /s /q "%%d"
)

REM Delete .sln, .vcxproj, and .vcxproj.filters files
for /r %%f in (*.sln *.vcxproj *.vcxproj.filters) do if exist "%%f" (
    echo Deleting file %%f
    del /f /q "%%f"
)

echo Cleanup complete.

REM Run the premake5 executable
call Build\Premake\premake5.exe vs2022 --file="Studio3D.Premake5.lua"

REM Pause the script to see the output
pause