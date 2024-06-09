#pragma once

#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Memory/Mem.h"

class CMaterial;
class CMesh;
class CShader;

struct SAsset
{
    ~SAsset()
    {
        Data = nullptr;
    }
    
    void* Data;
    size_t Size;
};

// Use ./Content/ as the base folder for any assets.
// Easily search or load any asset in that directory
// Use an Archive for each type.
class CAssetManager
{
    using SAssimpNode = aiNode;
    using SAssimpScene = aiScene;
    
public:
    void LoadMeshAsset(const std::string& Name, const std::string& Path);
    void LoadShaderAsset(const std::string& Name, const std::string& VSPath, const std::string& FSPath);
    void LoadTextureAsset(const std::string& Name, const std::string& Path);
    
    template<typename TAsset>
    TAsset* GetResource(const std::string& Name)
    {
        auto It = Data.find(Name);
        assert(It != Data.end() && "Asset does not exist.");
        return Cast<TAsset>(It->second->Data);
    }

protected:
    // Mesh File Loader Utility
    void ProcessNodeRecursive(aiNode* Node, const aiScene* Scene);
    void ProcessMesh(aiMesh *Mesh, const aiScene* Scene);
    CMaterial* ProcessMaterial(aiMaterial* Material);

    // Shader File Loader Utility
    std::string ReadShaderFile(const char* Path);
    //void RecompileShaderAsset();
    
private:
    std::unordered_map<std::string, SAsset*> Data; // Archive

    friend CAssetManager* GetResourceManager();

    static CAssetManager* GAssetManager;
};

static CAssetManager* GetResourceManager()
{
    if (!CAssetManager::GAssetManager)
    {
        CAssetManager::GAssetManager = new CAssetManager();
    }
    return CAssetManager::GAssetManager;
}