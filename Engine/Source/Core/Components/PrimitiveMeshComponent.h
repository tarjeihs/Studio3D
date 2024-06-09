#pragma once
#include "MeshComponent.h"
#include "Renderer/Mesh.h"

class CPrimitiveComponent : public CMeshComponent
{
public:
    CPrimitiveComponent(const EMeshType InPrimitiveType)
    {
        Mesh.Reset(new CMesh());
        Mesh->SetMaterial(new CMaterial());
        Mesh->GetMaterial()->AddShader(GetResourceManager()->GetResource<COpenGLShader>("DefaultShader"));
        
        SetPrimitiveType(InPrimitiveType);
    }
    
    void SetPrimitiveType(EMeshType NewPrimitiveType)
    {
        MeshType = NewPrimitiveType;
        switch (NewPrimitiveType)
        {
            case EMeshType::Cube:       SetPrimitiveTypeCube();     break;
            case EMeshType::Sphere:     SetPrimitiveTypeSphere();   break;
            case EMeshType::Capsule:    SetPrimitiveTypeCapsule();  break;
        }
    }

protected:
    void SetPrimitiveTypeCube();
    void SetPrimitiveTypeSphere();
    void SetPrimitiveTypeCapsule();
};
