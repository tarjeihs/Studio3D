#pragma once

#include <unordered_map>
#include "Memory/Memory.h"
#include "Shader.h"
#include "glm/fwd.hpp"
#include "glm/mat4x4.hpp"

class CTexture2D;
class CCameraComponent;

enum class EUniformType
{
    Mat4,
    Mat3,
    Vec4,
    Vec3,
    Vec2,
    Float,
    Int,
    Bool,
    Sampler2D
};

enum class EMaterialBlendMode
{
    Opaque,
    Masked,
    Translucent,
    Additive,
    Modulated
};

enum class EMaterialFlag : uint8
{
    TwoSided,
    DepthTest
};

struct SUniform
{
    std::string Name;
    EUniformType Type;

    union
    {
        glm::mat4 Mat4Value;
        glm::mat3 Mat3Value;
        glm::vec4 Vec4Value;
        glm::vec3 Vec3Value;
        glm::vec2 Vec2Value;
        float FloatValue;
        int32 IntValue;
        bool BoolValue;
        CTexture2D* Texture2DValue;
    };

    bool Dirty;

    SUniform() = default;
    SUniform(const std::string& name, EUniformType type, const glm::vec4& value) : Name(name), Type(type), Vec4Value(value), Dirty(true) {}
    SUniform(const std::string& name, EUniformType type, const glm::vec3& value) : Name(name), Type(type), Vec3Value(value), Dirty(true) {}
    SUniform(const std::string& name, EUniformType type, const glm::vec2& value) : Name(name), Type(type), Vec2Value(value), Dirty(true) {}
    SUniform(const std::string& name, EUniformType type, const glm::mat4& value) : Name(name), Type(type), Mat4Value(value), Dirty(true) {}
    SUniform(const std::string& name, EUniformType type, const glm::mat3& value) : Name(name), Type(type), Mat3Value(value), Dirty(true) {}
    SUniform(const std::string& name, EUniformType type, float value) : Name(name), Type(type), FloatValue(value), Dirty(true) {}
    SUniform(const std::string& name, EUniformType type, int32_t value) : Name(name), Type(type), IntValue(value), Dirty(true) {}
    SUniform(const std::string& name, EUniformType type, bool value) : Name(name), Type(type), BoolValue(value), Dirty(true) {}
    SUniform(const std::string& name, EUniformType type, CTexture2D* value) : Name(name), Type(type), Texture2DValue(value), Dirty(true) {}
};

// TODO: State caching, only affecting those values that change.
// TODO: Look into Render Sorting
class CMaterial
{
private:
    //TArray<TSharedPtr<CShader>> Shaders;
    TSharedPtr<CShader> Shader;

    std::unordered_map<std::string, SUniform> Uniforms;
    
public:
    virtual ~CMaterial() = default;

    void AddShader(CShader* Shader);
    CShader* GetShader(uint16 Index = 0) const;
    size_t GetShaderCount() const;

    void AddTexture(CTexture2D* Texture, uint8 Unit = 0);
    
    void SetParameter(const std::string& Name, const glm::vec4& Value);
    void SetParameter(const std::string& Name, const glm::vec3& Value);
    void SetParameter(const std::string& Name, const glm::vec2& Value);
    void SetParameter(const std::string& Name, float Value);
    void SetParameter(const std::string& Name, int32 Value);
    void SetParameter(const std::string& Name, bool Value);
    void SetParameter(const std::string& Name, const glm::mat4& Value);
    void SetParameter(const std::string& Name, const glm::mat3& Value);
    void SetParameter(const std::string& Name, CTexture2D* Value);

    // Bind the material (activate shader, bind textures, set uniforms)
    void Bind();

protected:
    void UploadUniform(uint32 ShaderID, const std::string& Name, const SUniform& Uniform);
};
