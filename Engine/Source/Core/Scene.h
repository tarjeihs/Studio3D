#pragma once
#include "Actor.h"
#include "Memory/Memory.h"

class CActor;

class CScene
{
public:
    template<typename TActor = CActor>
    TActor* SpawnActor()
    {
        static_assert(std::is_base_of<CActor, TActor>::value, "TActor must be derived from CActor");

        auto Actor = new CActor();
        
        Actors.Push(Actor);

        return Actor;
    }

    const TArray<CActor*>& GetActors()
    {
        return Actors;
    }
    
private:
    TArray<CActor*> Actors;
};
