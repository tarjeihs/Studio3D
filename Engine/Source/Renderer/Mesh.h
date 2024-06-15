#pragma once

#include "Memory/Memory.h"
#include "Material.h"
#include <vector>

#include "MaterialInstance.h"

class CMaterialInstance;

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

class CMesh
{
private:
    CMaterialInstance* MaterialInstance;

    SMeshAsset MeshAsset;
    
public:
    CMesh()
        : MaterialInstance(nullptr)
    {
    }
    
    virtual ~CMesh() = default;

    inline const SMeshAsset& GetMeshAsset() const
    {
        return MeshAsset;
    }

    inline CMaterial* GetMaterial() const
    {
        return MaterialInstance->BaseMaterial;
    }

    inline CMaterialInstance* GetMaterialInstance() const
    {
        return MaterialInstance;
    }

    void SetMaterialInstance(CMaterialInstance* NewMaterial)
    {
        MaterialInstance = NewMaterial;
    }

    void UploadAssetData(const std::vector<glm::vec3>& Vertices, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& UV0, const std::vector<uint32>& Indices, const std::vector<glm::vec3>& Tangents, const std::vector<glm::vec3>& BiTangents);

    // Draw Call
    void Draw();
};