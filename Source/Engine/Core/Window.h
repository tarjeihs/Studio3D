#pragma once

#include "../../../../Math/Source/MathTypes.h"

struct SWindowSpecification
{
    const char* Title;

    uint32 Width;

    uint32 Height;
};

class CWindow
{
protected:
    SWindowSpecification Specification;
    
    void* WindowHandle;
    
public:
    CWindow(const SWindowSpecification& InSpecification)
        : Specification(InSpecification)
    {
    }

    virtual ~CWindow() = default;
    
    virtual void CreateWindow() = 0;
    virtual void DestroyWindow() = 0;

    virtual void SwapAndPoll() = 0;
    virtual bool ShouldClose() const = 0;
};
