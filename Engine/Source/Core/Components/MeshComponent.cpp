#include "EnginePCH.h"
#include "MeshComponent.h"

#include <imgui.h>

#include "Core/Camera.h"
#include "Core/Engine.h"
#include "Core/Scene.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"

void CMeshComponent::Tick(float DeltaTime)
{
    if (Mesh.IsValid())
    {
        GetEngine()->GetRenderer()->Submit(Mesh.Get(), Mesh.Get()->GetMaterial(), Mesh.Get()->GetMaterialInstance(), Owner->Transform);
    }
}

void CMeshComponent::OnImGuiRender()
{
    float Color[3] = { Mesh->GetMaterialInstance()->GetParameter("lightColor").x, Mesh->GetMaterialInstance()->GetParameter("lightColor").y, Mesh->GetMaterialInstance()->GetParameter("lightColor").z };
    
    ImGui::Text("Vertices: %d", Mesh->GetMeshAsset().Vertices.size());
    ImGui::Text("Indices: %d", Mesh->GetMeshAsset().Indices.size());
    if (ImGui::ColorEdit3("Albedo", Color))
    {
        glm::vec3 Vec3 = glm::vec3(Color[0], Color[1], Color[2]);  
        Mesh->GetMaterialInstance()->SetParameter("lightColor", Vec3);
    }

    float SpecularStrength = Mesh->GetMaterialInstance()->GetParameterFloat("specularStrength");
    if (ImGui::DragFloat("Specular Strength", &SpecularStrength, 0.01f, 0.0f, 1.0f))
    {
        Mesh->GetMaterialInstance()->SetParameter("specularStrength", SpecularStrength);
    }

    float DiffuseStrength = Mesh->GetMaterialInstance()->GetParameterFloat("diffuseStrength");
    if (ImGui::DragFloat("Diffuse Strength", &DiffuseStrength, 0.01f, 0.0f, 1.0f))
    {
        Mesh->GetMaterialInstance()->SetParameter("diffuseStrength", DiffuseStrength);
    }

    float Shininess = Mesh->GetMaterialInstance()->GetParameterFloat("shininess");
    if (ImGui::DragFloat("Shininess", &Shininess, 1.0f, 0.0f, 32.0f))
    {
        Mesh->GetMaterialInstance()->SetParameter("shininess", Shininess);
    }

    float Roughness = Mesh->GetMaterialInstance()->GetParameterFloat("roughness");
    if (ImGui::DragFloat("Roughness", &Roughness, 0.01f, 0.0f, 1.0f))
    {
        Mesh->GetMaterialInstance()->SetParameter("roughness", Roughness);
    }

    float Metallic = Mesh->GetMaterialInstance()->GetParameterFloat("metallic");
    if (ImGui::DragFloat("Metallic", &Metallic, 0.01f, 0.0f, 1.0f))
    {
        Mesh->GetMaterialInstance()->SetParameter("metallic", Metallic);
    }
}
