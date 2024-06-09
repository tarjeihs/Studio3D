#pragma once

#include "Core/Actor.h"
#include "Object/Object.h"

class CComponent : public CObject
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
    
    virtual void Tick(float DeltaTime) 
    {
    }

    void Rename(const std::string& NewName)
    {
        Name = NewName;
    }
    
    const std::string& GetName() const
    {
        return Name;
    }
    
protected:
    using Super = CComponent;

    friend class CActor; 

    CActor* Owner;

    std::string Name;
};
