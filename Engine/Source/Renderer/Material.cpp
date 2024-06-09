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

void CMaterial::SetParameter(const std::string& Name, const glm::vec4& Value)
{
    Uniforms[Name] = { Name, EUniformType::Vec4, Value };
}

void CMaterial::SetParameter(const std::string& Name, const glm::vec3& Value)
{
    Uniforms[Name] = SUniform(Name, EUniformType::Vec3, Value);
}

void CMaterial::SetParameter(const std::string& Name, const glm::vec2& Value)
{
    Uniforms[Name] = SUniform(Name, EUniformType::Vec2, Value);
}

void CMaterial::SetParameter(const std::string& Name, float Value)
{
    Uniforms[Name] = SUniform(Name, EUniformType::Float, Value);
}

void CMaterial::SetParameter(const std::string& Name, int32 Value)
{
    Uniforms[Name] = SUniform(Name, EUniformType::Int, Value);
}

void CMaterial::SetParameter(const std::string& Name, bool Value)
{
    Uniforms[Name] = SUniform(Name, EUniformType::Bool, Value);
}

void CMaterial::SetParameter(const std::string& Name, const glm::mat4& Value)
{
    Uniforms[Name] = SUniform(Name, EUniformType::Mat4, Value);
}

void CMaterial::SetParameter(const std::string& Name, const glm::mat3& Value)
{
    Uniforms[Name] = SUniform(Name, EUniformType::Mat3, Value);
}

void CMaterial::SetParameter(const std::string& Name, CTexture2D* Value)
{
    Uniforms[Name] = SUniform(Name, EUniformType::Sampler2D, Value);
}

void CMaterial::UploadUniform(uint32 ShaderID, const std::string& Name, const SUniform& Uniform)
{
    int32 Location = glGetUniformLocation(ShaderID, Name.c_str());
    if (Location == -1) return;
    
    switch (Uniform.Type)
    {
        case EUniformType::Vec2:        glUniform2fv(Location, 1, glm::value_ptr(Uniform.Vec2Value)); break;
        case EUniformType::Vec3:        glUniform3fv(Location, 1, glm::value_ptr(Uniform.Vec3Value)); break;
        case EUniformType::Vec4:        glUniform4fv(Location, 1, glm::value_ptr(Uniform.Vec4Value)); break;
        case EUniformType::Mat3:        glUniformMatrix3fv(Location, 1, GL_FALSE, glm::value_ptr(Uniform.Mat3Value)); break;
        case EUniformType::Mat4:        glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Uniform.Mat4Value)); break;
        case EUniformType::Float:       glUniform1f(Location, Uniform.FloatValue); break;
        case EUniformType::Int:         glUniform1i(Location, Uniform.IntValue); break;
        case EUniformType::Bool:        glUniform1i(Location, Uniform.BoolValue); break;
        case EUniformType::Sampler2D:
        {
            glUniform1i(Location, 0);
            Uniform.Texture2DValue->Bind(0);
        }
    }
}

void CMaterial::Bind()
{
    for (auto& Pair : Uniforms)
    {
        SUniform& Uniform = Pair.second;

        if (!Uniform.Dirty) continue;

        Shader->Use();

        UploadUniform(Shader->GetShaderID(), Pair.first, Uniform);
        
        Uniform.Dirty = false;
    }
}