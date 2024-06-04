#pragma once

#include "../../Core/Window.h"

#define OPENGL_API

class CWindowsWindow final : public CWindow
{
public:
    explicit CWindowsWindow(const SWindowSpecification& InSpecification)
        : CWindow(InSpecification)
    {
    }

    virtual void CreateNativeWindow() override;
    virtual void DestroyWindow() override;

    virtual void Poll() override;
    virtual void Swap() override;
    
    virtual bool ShouldClose() const override;
};