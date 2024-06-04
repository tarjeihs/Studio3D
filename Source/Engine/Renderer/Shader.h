#pragma once
#include "fwd.hpp"
#include "../../../../Math/Source/MathTypes.h"
#include "../../../../Math/Source/Core/Vector3.h"
#include "../../../../Memory/Source/Core/Memory.h"
#include "../../../../Memory/Source/Core/StackAllocator.h"
#include "glad/glad.h"

enum class EShaderType : uint8 { Vertex, Fragment };

struct SShaderProgram
{
    std::string Source;

    const char* Name;

    uint32 ShaderID = 0;
};

struct SVertexBuffer
{
    SVertexBuffer(const float* Data, SizeType Size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, Size * sizeof(float), Data, GL_STATIC_DRAW);
    }
    
    ~SVertexBuffer()
    {
        glDeleteBuffers(1, &ID);
    }

    void Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Delete()
    {
        glDeleteBuffers(1, &ID);   
    }

private:
    uint32 ID;
};

struct SVertexArray
{
    SVertexArray()
    {
        glGenVertexArrays(1, &ID);
    }
    
    ~SVertexArray()
    {
        glDeleteVertexArrays(1, &ID);
    }

    void Bind()
    {
        glBindVertexArray(ID);
    }

    void Unbind()
    {
        glBindVertexArray(0);
    }

    void LinkAttrib(SVertexBuffer& VBO, uint32 Layout, uint32 Components, uint32 Type, int32 Stride, void* Offset)
    {
        VBO.Bind();
        glVertexAttribPointer(Layout, Components, Type, GL_FALSE, Stride, Offset);
        glEnableVertexAttribArray(Layout);
        VBO.Unbind();
    }

    void Delete()
    {
        glDeleteVertexArrays(1, &ID);
    }
    
    uint32 ID;
};

struct SIndexBuffer
{
    SIndexBuffer(const uint32* Indices, SizeType Size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size * sizeof(uint32), Indices, GL_STATIC_DRAW);
    }

    void Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Delete()
    {
        glDeleteBuffers(1, &ID);
    }

    uint32 ID;
};

class CShader
{
public:
    CShader()
        : VertexShaderProgram(MakeUniquePtr<SShaderProgram>()), FragmentShaderProgram(MakeUniquePtr<SShaderProgram>())
    {
    }
    
    virtual ~CShader() = default;
    
    virtual void Compile() = 0;
    virtual void Bind() = 0;
    virtual void Use() = 0;
    virtual void Delete() = 0;

    virtual void SetMat4(const std::string& Name, const glm::mat4& mat) const = 0;
    virtual void SetVec3(const std::string& Name, const glm::vec3& Vec3) const = 0;
    virtual void SetInt(const std::string& Name, int32 Value) const = 0;
    virtual void SetFloat(const std::string& Name, float Value) const = 0;
    virtual void SetBool(const std::string& Name, bool bValue) const = 0;
    
    FORCEINLINE uint32 GetShaderID() const;

    bool LoadSourceFile(const EShaderType ShaderType, const char* FilePath);

    //FORCEINLINE const SVertexArray& GetVAO() const
    //{
    //    return *VAO.Get();
    //}
//
    //FORCEINLINE const SVertexBuffer& GetVBO() const
    //{
    //    return *VBO.Get();
    //}
//
    //FORCEINLINE const SIndexBuffer& GetIBO() const
    //{
    //    return *IBO.Get();
    //}
    
protected:    
    TUniquePtr<SShaderProgram> VertexShaderProgram;
    TUniquePtr<SShaderProgram> FragmentShaderProgram;

    //TUniquePtr<SVertexArray> VAO;
    //TUniquePtr<SVertexBuffer> VBO;
    //TUniquePtr<SIndexBuffer> IBO;
    
    uint32 ShaderID = 0;
};

FORCEINLINE uint32 CShader::GetShaderID() const
{
    return ShaderID;
}
