#pragma once

#include "Core/Actor.h"

class CComponent
{
public:
    virtual ~CComponent()
    {
    }

    CActor* GetOwner() const
    {
        return Owner;
    }
    
    void SetOwner(CActor* NewOwner)
    {
        Owner = NewOwner;
    }
    
    virtual void Tick(float DeltaTime) {}

protected:
    using Super = CComponent;

    friend class CActor; 

    CActor* Owner;
};
