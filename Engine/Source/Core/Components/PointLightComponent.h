#pragma once
#include <glm/vec3.hpp>

#include "LightComponent.h"
#include "Core/AssetManager.h"

class CPointLightComponent final : public CLightComponent
{
    struct SPointLightData
    {
        glm::vec3 Position = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 Ambient = glm::vec3(0.1f, 0.1f, 0.1f); // Low intensity ambient light
        glm::vec3 Diffuse = glm::vec3(0.8f, 0.8f, 0.8f); // Standard diffuse light
        glm::vec3 Specular = glm::vec3(1.0f, 1.0f, 1.0f); // Bright specular highlights
        float Constant = 10.0f * 1; // No attenuation constant factor
        float Linear = 0.09f * 1; // Linear attenuation
        float Quadratic = 0.032f * 1; // Quadratic attenuation
        
        uint16 ShaderArrayIndex;
    } PointLightData;

public:
    //CPointLight()
    //{
    //    //PointLightData.ShaderArrayIndex = ++GPointLightCounter; // Do this and remove the Index + 1 in FS
    //    PointLightData.ShaderArrayIndex = GPointLightCounter++;
    //    GetResourceManager()->GetResource<CShader>("DefaultShader")->SetInt("PointLightCounter", GPointLightCounter);
    //}

    //~CPointLight()
    //{
    //    GPointLightCounter--;
    //    GetResourceManager()->GetResource<CShader>("DefaultShader")->SetInt("PointLightCounter", GPointLightCounter);
    //}

    virtual void Tick(float DeltaTime) override;
};
