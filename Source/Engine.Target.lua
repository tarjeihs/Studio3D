 project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "EnginePCH.h"
    pchsource "EnginePCH.cpp"

    files 
    { 
        "./**.h", 
        "./**.cpp",
    }

    includedirs 
    {
        "%{prj.location}",
        "../../GLFW/Source/Vendor/glfw/include",
        "../../GLAD/Source/Vendor/glad/include",
        "../../GLM/Source/Vendor/glm/glm",
    }

    links 
    {
        "GLFW",
        "GLAD",
        "GLM",
        "opengl32.lib"
    }

    defines 
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines 
        {
            "MOD_PLATFORM_WINDOWS",
            "MOD_BUILD_DLL",
        }

    filter "configurations:Debug"
        defines "MOD_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "MOD_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "MOD_DIST"
        runtime "Release"
        optimize "on"