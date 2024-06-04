#pragma once

#include <functional>

#include "../../../../Math/Source/MathTypes.h"

class CEvent;

struct SWindowSpecification
{
    const char* Title;

    uint32 Width;

    uint32 Height;
};

using EventCallbackFun = std::function<void(CEvent&)>;

struct SWindowUserData
{
    EventCallbackFun EventCallback;
};

class CWindow
{
protected:
    SWindowSpecification Specification;

    SWindowUserData UserData;
    
    void* WindowHandle;
    
public:
    CWindow(const SWindowSpecification& InSpecification)
        : Specification(InSpecification)
    {
    }

    virtual ~CWindow() = default;
    
    virtual void CreateWindow() = 0;
    virtual void DestroyWindow() = 0;

    virtual void Poll() = 0;
    virtual void Swap() = 0;
    
    virtual bool ShouldClose() const = 0;
    virtual void SetEventCallback(const EventCallbackFun& CallbackFun) = 0;

    inline void* GetWindowHandle() const
    {
        return WindowHandle;
    } 
};
