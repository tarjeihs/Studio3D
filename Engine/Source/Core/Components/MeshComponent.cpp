#include "EnginePCH.h"
#include "MeshComponent.h"

#include "Core/Camera.h"
#include "Core/Engine.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"

void CMeshComponent::Tick(float DeltaTime)
{
    if (Mesh.IsValid())
    {
        CEngine::Get()->GetRenderer()->Submit(Mesh.Get(), Mesh.Get()->GetMaterial(), CCamera::GCamera, Owner->Transform);
    }
}
