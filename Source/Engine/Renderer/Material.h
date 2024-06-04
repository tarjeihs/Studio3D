#pragma once
#include "../../../../Memory/Source/Core/Memory.h"
#include "Shader.h"
#include "Engine/Platform/OpenGL/OpenGLShader.h"

class CMaterial
{
private:
    TSharedPtr<CShader> Shader;
    
public:
    CMaterial()
        : Shader(nullptr)
    {
    }
    virtual ~CMaterial() = default;

    // Renders the material output of all shaders combined to this material
    void Render(const CCamera& Camera);
    
    inline CShader* GetShader() const
    {
        return Shader.Get();
    }

    void SetShader(COpenGLShader* NewShader)
    {
        Shader.Reset(NewShader);
    }
};
