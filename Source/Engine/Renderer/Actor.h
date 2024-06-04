#pragma once
#include "Mesh.h"
#include "Engine/Platform/OpenGL/OpenGLShader.h"

class CMesh;

class CActor
{
private:
    TSharedPtr<CMesh> Mesh;

public:
    CActor()
        : Mesh(nullptr)
    {
        WorldTransform.Location = glm::vec3(0.0f);
        WorldTransform.Rotation = glm::vec3(0.0f);
        WorldTransform.Scale = glm::vec3(1.0f);
    }
    virtual ~CActor() = default;

    virtual void Tick();
    
    inline CMesh* GetMesh() const
    {
        return Mesh.Get();
    }

    inline void SetMesh(CMesh* NewMesh)
    {
        Mesh.Reset(NewMesh);
    }

    inline void SetActorLocation(const glm::vec3& NewLocation)
    {
        WorldTransform.Location = NewLocation;
    }

    inline const glm::vec3& GetActorLocation() const
    {
        return WorldTransform.Location;
    }

    inline void SetActorRotation(const glm::vec3& NewRotation)
    {
        WorldTransform.Rotation = NewRotation;
    }

    inline const glm::vec3& GetActorRotation() const
    {
        return WorldTransform.Rotation;
    }

    inline void SetActorScale(const glm::vec3& NewScale)
    {
        WorldTransform.Scale = NewScale;
    }

    inline const glm::vec3& GetActorScale() const
    {
        return WorldTransform.Scale;
    }

public:
    FTransform WorldTransform;
};
