#include "EnginePCH.h"
#include "Mesh.h"
#include "glm/fwd.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

void CMesh::UploadAssetData(const std::vector<glm::vec3>& Vertices, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& UV0, const std::vector<uint32>& Indices)
{
    MeshAsset.Vertices.reserve(Vertices.size() + Normals.size() + UV0.size());
    MeshAsset.Indices = Indices;
    
    for (SizeType Index = 0; Index < Vertices.size(); ++Index)
    {
        MeshAsset.Vertices.push_back(Vertices[Index].x);
        MeshAsset.Vertices.push_back(Vertices[Index].y);
        MeshAsset.Vertices.push_back(Vertices[Index].z);

        MeshAsset.Vertices.push_back(Normals[Index].x);
        MeshAsset.Vertices.push_back(Normals[Index].y);
        MeshAsset.Vertices.push_back(Normals[Index].z);

        MeshAsset.Vertices.push_back(UV0[Index].x);
        MeshAsset.Vertices.push_back(UV0[Index].y);
    }

    MeshAsset.VAO = new SVertexArray();
    MeshAsset.VAO->Bind();
                  
    MeshAsset.VBO = new SVertexBuffer(MeshAsset.Vertices.data(), MeshAsset.Vertices.size());
    MeshAsset.IBO = new SIndexBuffer(MeshAsset.Indices.data(), Indices.size());
    
    MeshAsset.VAO->LinkAttribute(*MeshAsset.VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);                       // Position Attribute
    MeshAsset.VAO->LinkAttribute(*MeshAsset.VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));     // Normal Attribute
    MeshAsset.VAO->LinkAttribute(*MeshAsset.VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));     // UV0 Attribute

    MeshAsset.VAO->Unbind();
    MeshAsset.VBO->Unbind();
    MeshAsset.IBO->Unbind();
}

void CMesh::Draw()
{
    MeshAsset.VAO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<int32>(MeshAsset.Indices.size()), GL_UNSIGNED_INT, 0);
    MeshAsset.VAO->Unbind();
}
