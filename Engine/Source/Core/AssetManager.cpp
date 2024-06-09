#include "EnginePCH.h"
#include "AssetManager.h"

#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <stb_image.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture2D.h"

CAssetManager* CAssetManager::GAssetManager = nullptr;

void CAssetManager::LoadMeshAsset(const std::string& Name, const std::string& Path)
{
    Assimp::Importer Importer;

    const aiScene* Scene = Importer.ReadFile(Path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
    {
        std::string Error = Importer.GetErrorString();
    
        assert(false);
    }

    ProcessNodeRecursive(Scene->mRootNode, Scene);
}

//void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& sources)
void CAssetManager::LoadShaderAsset(const std::string& Name, const std::string& VSPath, const std::string& FSPath)
{
    COpenGLShader* Shader = new COpenGLShader();
    Shader->VertexShaderProgram->Source = ReadShaderFile(VSPath.c_str());
    Shader->FragmentShaderProgram->Source = ReadShaderFile(FSPath.c_str());
    Shader->Compile();

    SAsset* Asset = new SAsset();
    Asset->Data = Shader;
    Asset->Size = sizeof(COpenGLShader);

    Data.insert(std::make_pair(Name, Asset));
}

// WARNING: Are we writing to TextureID?
void CAssetManager::LoadTextureAsset(const std::string& Name, const std::string& Path)
{
    CTexture2D* Texture2D = new CTexture2D();
    stbi_set_flip_vertically_on_load(true); // Flip the image
    uint8* ImageData = stbi_load(Path.c_str(), &Texture2D->Width, &Texture2D->Height, &Texture2D->Channels, 0);

    Texture2D->Bind(0);
    
    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    uint32 Format;
    switch (Texture2D->Channels)
    {
        case 1: Format = GL_RED; break;
        case 3: Format = GL_RGB; break;
        case 4: Format = GL_RGBA; break;
        default: Format = 0;
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // https://stackoverflow.com/a/58927549/4638518
    glTexImage2D(GL_TEXTURE_2D, 0, Format, Texture2D->Width, Texture2D->Height, 0, Format, GL_UNSIGNED_BYTE, ImageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(ImageData);

    SAsset* Asset = new SAsset();
    Asset->Data = Texture2D;
    Asset->Size = sizeof(CTexture2D);
    
    Data.insert(std::make_pair(Name, Asset));
}

void CAssetManager::ProcessNodeRecursive(aiNode* Node, const aiScene* Scene)
{
    for (uint32 Index = 0; Index < Node->mNumMeshes; Index++)
    {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[Index]];
        ProcessMesh(Mesh, Scene);
    }

    for (uint32 Index = 0; Index < Node->mNumChildren; Index++)
    {
        ProcessNodeRecursive(Node->mChildren[Index], Scene);
    }
}

void CAssetManager::ProcessMesh(aiMesh* Mesh, const aiScene* Scene)
{
    CMesh* NewMesh = new CMesh();

    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec2> TexCoord;
    std::vector<uint32> Indices;
    
    // Process vertices
    for (uint32 Index = 0; Index < Mesh->mNumVertices; Index++)
    {
        aiVector3D Position = Mesh->mVertices[Index];
        aiVector3D Normal = Mesh->mNormals[Index];
        aiVector3D UV0 = aiVector3D(0.0f, 0.0f, 0.0f);
        if (Mesh->mTextureCoords[0])
        {
            UV0 = Mesh->mTextureCoords[0][Index];
        }

        Vertices.push_back({ Position.x, Position.y, Position.z });
        Normals.push_back( { Normal.x, Normal.y, Normal.z });
        TexCoord.push_back({ UV0.x, UV0.y });
    }

    // Process indices
    for (unsigned int i = 0; i < Mesh->mNumFaces; i++)
    {
        aiFace face = Mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            Indices.push_back(face.mIndices[j]);
        }
    }

    NewMesh->UploadAssetData(Vertices, Normals, TexCoord, Indices);

    CMaterial* Material = new CMaterial();
    NewMesh->SetMaterial(Material);

    Material->AddShader(GetResourceManager()->GetResource<COpenGLShader>("DefaultShader"));
    
    aiMaterial* MaterialImport = Scene->mMaterials[Mesh->mMaterialIndex];
    if (MaterialImport->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString TexturePath;
        MaterialImport->GetTexture(aiTextureType_DIFFUSE, 0, &TexturePath);
        LoadTextureAsset(TexturePath.C_Str(), TexturePath.C_Str());
        Material->SetParameter("TexSampleDiffuse", GetResourceManager()->GetResource<CTexture2D>(TexturePath.C_Str()));
    }
    
    SAsset* Asset = new SAsset();
    Asset->Data = NewMesh;
    Asset->Size = sizeof(CMesh);

    std::string Name = Mesh->mName.C_Str();
    Data.insert(std::make_pair("Model", Asset));
}

CMaterial* CAssetManager::ProcessMaterial(aiMaterial* Material)
{
    CMaterial* NewMaterial = new CMaterial();
    
    if (Material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString TexturePath;
        Material->GetTexture(aiTextureType_DIFFUSE, 0, &TexturePath);
        LoadTextureAsset(Material->GetName().C_Str(), TexturePath.C_Str());
        NewMaterial->SetParameter("TexSampleDiffuse", GetResourceManager()->GetResource<CTexture2D>(Material->GetName().C_Str()));
    }

    //if (Material->GetTextureCount(aiTextureType_NORMALS) > 0)
    //{
    //    aiString TexturePath;
    //    Material->GetTexture(aiTextureType_DIFFUSE, 0, &TexturePath);
    //    LoadTextureAsset(Material->GetName().C_Str(), TexturePath.C_Str());
    //}

    //aiColor3D aiAmbientColor(0.0f, 0.0f, 0.0f);
    //if (AI_SUCCESS == Material->Get(AI_MATKEY_COLOR_AMBIENT, aiAmbientColor))
    //{
    //    glm::vec3 AmbientColor(aiAmbientColor.r, aiAmbientColor.g, aiAmbientColor.b);
    //    NewMaterial->SetUniform("AmbientColor", AmbientColor);
    //}
    return NewMaterial;
}

std::string CAssetManager::ReadShaderFile(const char* Path)
{
    std::ifstream File(Path);
    std::stringstream FileBuffer;
    
    FileBuffer << File.rdbuf();
    File.close();
    return FileBuffer.str();
}
