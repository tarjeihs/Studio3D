#include "EnginePCH.h"
#include "Actor.h"
#include "Component.h"

void CActor::Tick(float DeltaTime)
{
    for (CComponent* Component : Components)
    {
        Component->Tick(DeltaTime);   
    }
}
