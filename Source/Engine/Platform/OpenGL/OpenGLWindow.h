#pragma once

#include "../../Core/Window.h"

#define OPENGL_API

class COpenGLWindow final : public CWindow
{
public:
    explicit COpenGLWindow(const SWindowSpecification& InSpecification)
        : CWindow(InSpecification)
    {
    }

    virtual void CreateWindow() override;
    virtual void DestroyWindow() override;

    virtual void SwapAndPoll() override;
    virtual bool ShouldClose() const override;
};