#pragma once
#include "Material.h"
#include "Texture2D.h"


/*
 * Specialized version of CMaterial.
 * Allows for overriding specific parameters without duplicating the entire material.
 * Each set can have its own set of uniform values. 
 */
class CMaterialInstance
{
public:
    CMaterial* BaseMaterial;

    std::unordered_map<std::string, SUniform> Uniforms;

    uint8 TextureIndexCounter;

public:
    CMaterialInstance(CMaterial* InBaseMaterial)
    {
        BaseMaterial = InBaseMaterial;

        // Default values
        SetParameter("lightColor", glm::vec3(1));
        SetParameter("ambientStrength", 0.1f);
        SetParameter("diffuseStrength", 1.0f);
        SetParameter("specularStrength", 0.5f);
        SetParameter("shininess", 32.0f);
        SetParameter("roughness", 0.5f);
        SetParameter("metallic", 0.0f);
    }

    void SetParameter(const std::string& Name, const glm::vec4& Value)
    {
        Uniforms[Name] = { Name, EUniformType::Vec4, Value };
    }

    void SetParameter(const std::string& Name, const glm::vec3& Value)
    {
        Uniforms[Name] = SUniform(Name, EUniformType::Vec3, Value);
    }

    void SetParameter(const std::string& Name, const glm::vec2& Value)
    {
        Uniforms[Name] = SUniform(Name, EUniformType::Vec2, Value);
    }

    void SetParameter(const std::string& Name, float Value)
    {
        Uniforms[Name] = SUniform(Name, EUniformType::Float, Value);
    }

    void SetParameter(const std::string& Name, int32 Value)
    {
        Uniforms[Name] = SUniform(Name, EUniformType::Int, Value);
    }

    void SetParameter(const std::string& Name, bool Value)
    {
        Uniforms[Name] = SUniform(Name, EUniformType::Bool, Value);
    }

    void SetParameter(const std::string& Name, const glm::mat4& Value)
    {
        Uniforms[Name] = SUniform(Name, EUniformType::Mat4, Value);
    }

    void SetParameter(const std::string& Name, const glm::mat3& Value)
    {
        Uniforms[Name] = SUniform(Name, EUniformType::Mat3, Value);
    }

    void SetParameter(const std::string& Name, CTexture2D* Value)
    {
        Uniforms[Name] = SUniform(Name, EUniformType::Sampler2D, Value);
    }

    const glm::vec3& GetParameter(const std::string& Name)
    {
        return Uniforms[Name].Vec3Value;
    }

    float GetParameterFloat(const std::string& Name)
    {
        return Uniforms[Name].FloatValue;
    }
    
    virtual void Bind();
    
    void UploadUniformToGPU(const std::string& Name, const SUniform& Uniform);
};
