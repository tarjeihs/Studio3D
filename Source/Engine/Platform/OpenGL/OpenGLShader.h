#pragma once
#include "Engine/Renderer/Shader.h"

class COpenGLShader : public CShader
{
public:
    virtual void Compile() override;
    virtual void Render() override;
    virtual void Delete() override;

    virtual void SetVec3(const std::string& Name, const SVector3f& Vec3) const override;
    virtual void SetInt(const std::string& Name, int32 Value) const override;
    virtual void SetFloat(const std::string& Name, float Value) const override;
    virtual void SetBool(const std::string& Name, bool bValue) const override;
};