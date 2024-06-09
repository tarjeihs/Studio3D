#include "EnginePCH.h"
#include "PointLightComponent.h"

void CPointLightComponent::Tick(float DeltaTime)
{
    std::string Index = std::to_string(PointLightData.ShaderArrayIndex);

    CShader* Shader = GetResourceManager()->GetResource<CShader>("DefaultShader");
    
    Shader->SetVector3("PointLights[" + Index + "].Position", PointLightData.Position);
    Shader->SetVector3("PointLights[" + Index + "].Ambient", PointLightData.Ambient);
    Shader->SetVector3("PointLights[" + Index + "].Specular", PointLightData.Specular);
    Shader->SetVector3("PointLights[" + Index + "].Diffuse", PointLightData.Diffuse);
    Shader->SetFloat("PointLights[" + Index + "].Constant", PointLightData.Constant);
    Shader->SetFloat("PointLights[" + Index + "].Linear", PointLightData.Linear);
    Shader->SetFloat("PointLights[" + Index + "].Quadratic", PointLightData.Quadratic);
}
