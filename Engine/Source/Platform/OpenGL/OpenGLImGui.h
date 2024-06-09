#pragma once
#include "UI/ImGui.h"

class COpenGLImGui : public CImGui
{
public:
    virtual void Enable() override;
    virtual void Disable() override;
    virtual void BeginFrame() override;
    virtual void EndFrame() override;
    virtual void OnRender(float DeltaTime) override;
};
