#pragma once

#include <glm/vec3.hpp>

#include "Core/AssetManager.h"
#include "Math/Transform.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Memory/Mem.h"
#include "Object/Object.h"

class CComponent;

class CActor : public CObject
{
public:
    CActor(const std::string& InName)
        : Name(InName)
    {
        Transform.Location = glm::vec3(0.0f);
        Transform.Rotation = glm::vec3(0.0f);
        Transform.Scale = glm::vec3(1.0f);
    }

    virtual ~CActor()
    {
    }

    virtual void Tick(float DeltaTime);

    template<typename TComponent, typename... TArgs>
    TComponent* AddComponent(const std::string& Name, TArgs&&... Args)
    {
        TComponent* Component = new TComponent(std::forward<TArgs>(Args)...);
        Component->SetOwner(this);
        Component->Rename(Name);
        Components.Push(Component);
        return Component;
    }

    template<typename TComponent>
    TComponent* GetComponent() const
    {
        for (CComponent* Component : Components)
        {
            if (TComponent* CastedComponent = dynamic_cast<TComponent*>(Component))
            {
                return CastedComponent;
            }
        }
        return nullptr;
    }

    TArrayView<CComponent*> GetComponents() const
    {
        return TArrayView(Components);
    }

    inline void AddLocation(const glm::vec3& NewLocation)
    {
        Transform.Location += NewLocation;
    }
    
    inline void SetActorLocation(const glm::vec3& NewLocation)
    {
        Transform.Location = NewLocation;
    }

    inline const glm::vec3& GetActorLocation() const
    {
        return Transform.Location;
    }

    inline void SetActorRotation(const glm::vec3& NewRotation)
    {
        Transform.Rotation = NewRotation;
    }

    inline const glm::vec3& GetActorRotation() const
    {
        return Transform.Rotation;
    }

    inline void SetActorScale(const glm::vec3& NewScale)
    {
        Transform.Scale = NewScale;
    }

    inline const glm::vec3& GetActorScale() const
    {
        return Transform.Scale;
    }

protected:
    using Super = CActor;
    
public:
    STransform Transform;

    TArray<CComponent*> Components;

    std::string Name;

private:
    friend class CComponent;
};