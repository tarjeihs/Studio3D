#pragma once

#include <functional>

#include "../../../../Math/Source/MathTypes.h"

class CInput;
class CEvent;

struct SWindowSpecification
{
    const char* Title;

    uint32 Width;

    uint32 Height;
};

struct SWindowUserData
{
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
    
    virtual void CreateNativeWindow() = 0;
    virtual void DestroyWindow() = 0;

    virtual void Poll() = 0;
    virtual void Swap() = 0;
    
    virtual bool ShouldClose() const = 0;

    inline void* GetNativeWindow() const
    {
        return WindowHandle;
    } 
};
