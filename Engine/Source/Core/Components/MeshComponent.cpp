#include "EnginePCH.h"
#include "MeshComponent.h"

#include "Core/Camera.h"
#include "Core/Engine.h"
#include "Core/Scene.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"

//SFieldRegistrar* CMeshComponent::Field1 = new SFieldRegistrar(EMetaFieldType::Int32, "Field1");

void CMeshComponent::Tick(float DeltaTime)
{
    if (Mesh.IsValid())
    {
        CEngine::Get()->GetRenderer()->Submit(Mesh.Get(), Mesh.Get()->GetMaterial(), Owner->Transform);
    }
}
