#pragma once

#include <dinput.h>

#include "../../../../Memory/Source/Core/Memory.h"
#include "Material.h"

struct SMeshAsset
{
    uint8 Stride = 8; // Position: 3 + Normal: 3 + UV0: 2
    std::vector<float> Vertices;
    std::vector<uint32> Indices;
    //std::vector<glm::vec3> Vertices;
    //std::vector<glm::vec3> Normals;
    //std::vector<glm::vec3> UV0;

    SVertexArray* VAO;
    SVertexBuffer* VBO;
    SIndexBuffer* IBO;

    inline const float* GetVertices() const
    {
        return nullptr;
    }
};

class CMesh
{
private:
    TSharedPtr<CMaterial> Material;

    SMeshAsset MeshAsset;
    
public:
    CMesh()
        : Material(nullptr)
    {
    }
    
    virtual ~CMesh() = default;

    inline CMaterial* GetMaterial() const
    {
        return Material.Get();
    }

    inline const SMeshAsset& GetMeshAsset() const
    {
        return MeshAsset;
    }

    void SetMaterial(CMaterial* NewMaterial)
    {
        Material.Reset(NewMaterial);
    }

    void UploadAssetData(const std::vector<glm::vec3>& Vertices, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& UV0, const std::vector<uint32>& Indices);

    void Render();
};