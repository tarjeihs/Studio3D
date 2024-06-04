#pragma once

#include "../../Core/Window.h"
#include "GLFW/glfw3.h"

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

    virtual void Poll() override;
    virtual void Swap() override;
    
    virtual bool ShouldClose() const override;

    inline void SetEventCallback(const EventCallbackFun& Callback) override
    {
        UserData.EventCallback = Callback;
    }

protected:
};