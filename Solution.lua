workspace "Engine"
    architecture "x86_64"
    startproject "Engine"

    configurations 
    { 
        "Debug", 
        "Release", 
        "Dist" 
    }

    flags 
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Module Dependency"
        include "../GLFW/Source/GLFW.Target.lua"
        include "../GLAD/Source/GLAD.Target.lua"
    group ""

    group "My Module"
        include "Source/Engine.Target.lua"
    group ""