#pragma once

#include "Core/Actor.h"

class CComponent
{
public:
    virtual ~CComponent()
    {
    }

    void SetOwner(CActor* NewOwner)
    {
        Owner = NewOwner;
    }
    
    virtual void Tick(float DeltaTime) = 0;

    CActor* Owner;

protected:
    using Super = CComponent;

    friend class CActor; 
};
