#pragma once
#include "MeshComponent.h"
#include "Renderer/Mesh.h"

class CPrimitiveComponent : public CMeshComponent
{
public:
    CPrimitiveComponent(const EMeshType InPrimitiveType)
    {
        CMaterial* Material = new CMaterial();
        Material->AddShader(GetResourceManager()->GetResource<COpenGLShader>("DefaultShader"));
        CMaterialInstance* MaterialInstance = new CMaterialInstance(Material);
        
        Mesh.Reset(new CMesh());
        Mesh->SetMaterialInstance(MaterialInstance);
        
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
