#pragma once
#include "fwd.hpp"
#include "vec3.hpp"
#include "Engine/Core/Camera.h"
#include "Engine/Renderer/Shader.h"

class COpenGLShader : public CShader
{
public:
    virtual void Compile() override;
    virtual void Bind() override {}
    virtual void Use() override;
    virtual void Delete() override;

    virtual void SetMat4(const std::string& Name, const glm::mat4& Matrix) const override;
    virtual void SetVec3(const std::string& Name, const glm::vec3& Vec3) const override;
    virtual void SetInt(const std::string& Name, int32 Value) const override;
    virtual void SetFloat(const std::string& Name, float Value) const override;
    virtual void SetBool(const std::string& Name, bool bValue) const override;
};