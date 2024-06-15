#include "EnginePCH.h"
#include "Material.h"

#include <glm/gtc/type_ptr.hpp>

#include "Texture2D.h"

void CMaterial::AddShader(CShader* InShader)
{
    //Shaders.Push(TSharedPtr(Shader));
    Shader.Reset(InShader);
}

CShader* CMaterial::GetShader(uint16 Index) const
{
    //return Shaders[Index].Get();
    return Shader.Get();
}

size_t CMaterial::GetShaderCount() const
{
    //return Shaders.GetSize(); 
    return 1; 
}

void CMaterial::Bind()
{
    Shader->Use();
    //ParameterBuffer->Bind();
    
    //for (auto& Pair : Uniforms)
    //{
    //    SUniform& Uniform = Pair.second;
    //
    //    if (!Uniform.Dirty) continue;
    //    
    //    UploadUniform(Shader->GetShaderID(), Pair.first, Uniform);
    //    
    //    Uniform.Dirty = false;
    //}
}