#include "EnginePCH.h"
#include "Actor.h"

void CActor::Tick()
{
    // Default Vertex Shader Parameters
    GetMesh()->GetMaterial()->GetShader()->Use();
    GetMesh()->GetMaterial()->GetShader()->SetMat4("projection", CCamera::GCamera->GetProjectionMatrix());
    GetMesh()->GetMaterial()->GetShader()->SetMat4("view", CCamera::GCamera->GetViewMatrix());
    GetMesh()->GetMaterial()->GetShader()->SetMat4("model", CCamera::GetViewModel(WorldTransform));
    GetMesh()->Render();
}
