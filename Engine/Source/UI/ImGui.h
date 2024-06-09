#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Core/Engine.h"
#include "Core/Window.h"

class CImGui
{
public:
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void OnRender(float DeltaTime) = 0;
};

static inline CImGui* GetImGui()
{
    return CEngine::Get()->GetImGui();
}
