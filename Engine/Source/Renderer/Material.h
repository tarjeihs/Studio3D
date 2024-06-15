#pragma once

#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

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

//class CUniformBuffer
//{
//public:
//    GLuint BufferID;
//    
//    std::unordered_map<std::string, GLint> UniformLocations;
//    std::unordered_map<std::string, SUniform> Uniforms;
//
//
//    CUniformBuffer(uint32 ShaderID)
//    {
//        glGenBuffers(1, &BufferID);
//
//        // Retrieve and store uniform locations
//        GLint uniformCount;
//        glGetProgramiv(ShaderID, GL_ACTIVE_UNIFORMS, &uniformCount);
//        char name[256];
//        for (int i = 0; i < uniformCount; ++i)
//        {
//            GLsizei length;
//            glGetActiveUniformName(ShaderID, i, sizeof(name), &length, name);
//            GLint location = glGetUniformLocation(ShaderID, name);
//            UniformLocations[name] = location;
//        }
//    }
//
//    ~CUniformBuffer()
//    {
//        glDeleteBuffers(1, &BufferID);
//    }
//};

// TODO: State caching, only affecting those values that change.
// TODO: Look into Render Sorting
class CMaterial
{
protected:
    //TArray<TSharedPtr<CShader>> Shaders;
    TSharedPtr<CShader> Shader;

public:
    virtual ~CMaterial() = default;

    void AddShader(CShader* Shader);
    CShader* GetShader(uint16 Index = 0) const;
    size_t GetShaderCount() const;

    void AddTexture(CTexture2D* Texture, uint8 Unit = 0);
    
    // Bind the material (activate shader, bind textures, set uniforms)
    virtual void Bind();
};
