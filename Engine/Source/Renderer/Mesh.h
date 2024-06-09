#pragma once

#include "Memory/Memory.h"
#include "Material.h"
#include <vector>

struct SMeshAsset
{
    uint8 Stride = 8; // Position: 3 + Normal: 3 + UV0: 2
    std::vector<float> Vertices;
    std::vector<uint32> Indices;

    SVertexArray* VAO;
    SVertexBuffer* VBO;
    SIndexBuffer* IBO;

    inline const float* GetVertices() const
    {
        return nullptr;
    }
};

struct SVertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoor;
    int TriangleIndex;
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

    inline const SMeshAsset& GetMeshAsset() const
    {
        return MeshAsset;
    }

    inline CMaterial* GetMaterial() const
    {
        return Material.Get();
    }

    void SetMaterial(CMaterial* NewMaterial)
    {
        Material.Reset(NewMaterial);
    }

    void UploadAssetData(const std::vector<glm::vec3>& Vertices, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& UV0, const std::vector<uint32>& Indices);

    void Draw();
};