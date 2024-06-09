#pragma once
#include "Core/Component.h"
#include "Math/MathTypes.h"
#include "Core/AssetManager.h"
#include "Renderer/Shader.h"

class CLightComponent : public CComponent
{
    static uint16 GPointLightCounter;

public:
    CLightComponent()
    {
        ShaderArrayIndex = GPointLightCounter++;
        GetResourceManager()->GetResource<CShader>("DefaultShader")->SetInt("LightCounter", GPointLightCounter);
    }

    ~CLightComponent()
    {
        GPointLightCounter--;
        GetResourceManager()->GetResource<CShader>("DefaultShader")->SetInt("LightCounter", GPointLightCounter);
    }

protected:
    uint16 ShaderArrayIndex = sizeof(uint16);
};
