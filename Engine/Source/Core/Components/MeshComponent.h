#pragma once
#include "Core/Component.h"

class CMesh;

enum class EMeshType
{
    Custom,

    Cube,

    Sphere,

    Capsule
};

class CMeshComponent : public CComponent
{
public:
    CMeshComponent()
        : Mesh(nullptr), MeshType(EMeshType::Custom)
    {
    }

    virtual void Tick(float DeltaTime);
    virtual void OnImGuiRender() override;
    
    inline CMesh* GetMesh() const
    {
        return Mesh.Get();
    }
    
    inline void SetMesh(CMesh* NewMesh)
    {
        if (MeshType == EMeshType::Custom)
        {
            Mesh.Reset(NewMesh);
        }
    }

protected:
    TSharedPtr<CMesh> Mesh;

    EMeshType MeshType;
};

