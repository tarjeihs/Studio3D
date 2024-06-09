#pragma once
#include "Actor.h"
#include "Camera.h"
#include "Memory/Memory.h"

class CActor;
class CCameraComponent;

class CScene
{
public:
    template<typename TActor = CActor>
    TActor* SpawnActor(const std::string& Name = "Unnamed_Actor")
    {
        static_assert(std::is_base_of<CActor, TActor>::value, "TActor must be derived from CActor.");
        
        auto Actor = new TActor(Name);
        
        Actors.Push(Actor);

        Metrics.CurrentActorCount++;
        Metrics.TotalActorCount++;

        return Actor;
    }

    template<typename TActor = CActor>
    TActor* GetActorOfType()
    {
        static_assert(std::is_base_of<CActor, TActor>::value, "TActor must be derived from CActor.");
        
        for (CActor* Actor : Actors)
        {
            TActor* FoundActor = dynamic_cast<TActor*>(Actor);
            if (FoundActor != nullptr)
            {
                return FoundActor;
            }
        }
        return nullptr;
    }

    void Tick(float DeltaTime)
    {
        ActiveCamera->CalculateCameraTransform();
    }

    const TArray<CActor*>& GetActors()
    {
        return Actors;
    }

    CCameraComponent* GetActiveCamera() const
    {
        return ActiveCamera.Get();
    }

    void SetActiveCamera(CCameraComponent* NewActiveCamera)
    {
        ActiveCamera.Reset(NewActiveCamera);
    }
    
    struct SMetrics
    {
        uint32 CurrentActorCount;
        uint32 TotalActorCount;
    };
    SMetrics Metrics;

private:
    TArray<CActor*> Actors;

    TSharedPtr<CCameraComponent> ActiveCamera;
};

static inline CScene* GetScene()
{
    return CEngine::Get()->GetScene();
}