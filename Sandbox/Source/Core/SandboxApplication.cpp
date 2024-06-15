#include <iostream>

#include "Core/Application.h"
#include "Core/AssetManager.h"
#include "Core/Input.h"
#include "Core/KeyCode.h"
#include "Core/Scene.h"
#include "Core/Window.h"
#include "Core/Components/MeshComponent.h"
#include "Core/Components/PointLightComponent.h"
#include "Core/Components/PrimitiveMeshComponent.h"
#include "Renderer/MaterialInstance.h"

class CEditorEngine : public CEngine
{
public:
    virtual void OnStart() override
    {
        //GetResourceManager()->LoadMeshAsset("Sponza", "D:/Laboratory/Modules/Studio3D/Engine/Content/sponza/source/Sponza/Sponza.fbx");
        //const SAsset& MeshAsset = GetResourceManager()->GetAsset("Sponza");
        
        //CMaterial* Mat = new CMaterial();
        //Mat->AddShader(GetResourceManager()->GetResource<COpenGLShader>("DefaultShader"));
        
        //for (int32 Index = 0; Index < MeshAsset.Data.GetSize(); ++Index)
        //{
        //    CActor* MeshActor = GetScene()->SpawnActor("MeshActor_" + std::to_string(Index)); 
        //    CMeshComponent* MeshComponent = MeshActor->AddComponent<CMeshComponent>(R"(MeshComp)");
        //    MeshComponent->SetMesh(Cast<CMesh>(MeshAsset.Data[Index]));
//
        //    CMaterialInstance* Instance = new CMaterialInstance(Mat);
        //    MeshComponent->GetMesh()->SetMaterialInstance(Instance);
        //}
        GetResourceManager()->LoadShaderAsset("DefaultShader", "D:/Laboratory/Modules/Studio3D/Engine/Source/Shaders/DefaultVS.glsl", "D:/Laboratory/Modules/Studio3D/Engine/Source/Shaders/DefaultFS.glsl");
        GetResourceManager()->LoadMeshAsset("drone", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/D-21-11.fbx");

        GetResourceManager()->LoadTextureAsset("albedo", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/textures/d-21-11-v0-diffuse-alt.png");
        GetResourceManager()->LoadTextureAsset("ao", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/textures/d-21-11-v0-ao.png");
        GetResourceManager()->LoadTextureAsset("normal", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/textures/d-21-11-v0-normal.png");
        GetResourceManager()->LoadTextureAsset("metalness", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/textures/d-21-11-v0-metalness.png");
        GetResourceManager()->LoadTextureAsset("roughness", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/textures/d-21-11-v0-roughness.png");

        CMaterial* SimpleColorMaterial = new CMaterial(); // TODO: Implement
        
        CActor* MeshActor = GetScene()->SpawnActor("MeshActor");
        CMeshComponent* MeshComponent = MeshActor->AddComponent<CMeshComponent>(R"(MeshComp)");
        MeshComponent->SetMesh(GetResourceManager()->GetResource<CMesh>("drone"));
        MeshComponent->GetMesh()->GetMaterialInstance()->SetParameter("albedo", GetResourceManager()->GetResource<CTexture2D>("albedo"));
        MeshComponent->GetMesh()->GetMaterialInstance()->SetParameter("ao", GetResourceManager()->GetResource<CTexture2D>("ao"));
        MeshComponent->GetMesh()->GetMaterialInstance()->SetParameter("normal", GetResourceManager()->GetResource<CTexture2D>("normal"));
        MeshComponent->GetMesh()->GetMaterialInstance()->SetParameter("metalness", GetResourceManager()->GetResource<CTexture2D>("metalness"));
        MeshComponent->GetMesh()->GetMaterialInstance()->SetParameter("roughness", GetResourceManager()->GetResource<CTexture2D>("roughness"));
        
        CActor* Sphere = GetScene()->SpawnActor("Sphere");
        Sphere->SetActorLocation({3.0f, 0.0f, 0.0f});
        Sphere->AddComponent<CPrimitiveComponent>(R"(SphereMeshComp)", EMeshType::Sphere);

        CActor* Cube = GetScene()->SpawnActor("Cube");
        Cube->SetActorLocation({-2.f, 0.0f, 0.0f});
        Cube->AddComponent<CPrimitiveComponent>(R"(CubeMeshComp)", EMeshType::Cube);

        CActor* Capsule = GetScene()->SpawnActor("Capsule");
        Capsule->SetActorLocation({-3.0f, 0.0f, 3.0f});
        Capsule->AddComponent<CPrimitiveComponent>(R"(CapsuleMeshComp)", EMeshType::Capsule);

        Player = GetScene()->SpawnActor("Player");
        Player->SetActorLocation(glm::vec3(0.0f, 0.0f, 2.5f));
        CCameraComponent* Camera = Player->AddComponent<CCameraComponent>(R"(CameraComponent)");
        GetScene()->SetActiveCamera(Camera);
    }

    float CameraSpeed = 5.0f;
    bool bDebugDraw = false;
    bool bCursorMode = false;

    virtual void OnUpdate(float DeltaTime) override
    {
        CCameraComponent* CameraComponent = Player->GetComponent<CCameraComponent>();
        
        if (CInput::KeyPress(S3D_KEY_W))
        {
            Player->AddLocation(CameraSpeed * CameraComponent->Front * GetEngine()->Time.GetDeltaTime());
        }
        if (CInput::KeyPress(S3D_KEY_S))
        {
            Player->AddLocation(-(CameraSpeed * CameraComponent->Front * GetEngine()->Time.GetDeltaTime()));
        }
        if (CInput::KeyPress(S3D_KEY_D))
        {
            Player->AddLocation(CameraSpeed * glm::normalize(glm::cross(CameraComponent->Front, CameraComponent->Up)) * GetEngine()->Time.GetDeltaTime());
        }
        if (CInput::KeyPress(S3D_KEY_A))
        {
            Player->AddLocation(-(CameraSpeed * glm::normalize(glm::cross(CameraComponent->Front, CameraComponent->Up)) * GetEngine()->Time.GetDeltaTime()));
        }
        if (CInput::KeyPress(S3D_KEY_SPACE))
        {
            Player->AddLocation(CameraComponent->WorldUp * CameraSpeed * GetEngine()->Time.GetDeltaTime());
        }
        if (CInput::KeyPress(S3D_KEY_LEFT_SHIFT))
        {
            Player->AddLocation(-(CameraComponent->WorldUp * CameraSpeed * GetEngine()->Time.GetDeltaTime()));
        }
        if (CInput::KeyHold(S3D_KEY_F1, 0.02f))
        {
            if (bDebugDraw)
            {
                bDebugDraw = false;
                GetResourceManager()->GetResource<COpenGLShader>("DefaultShader")->SetBool("bDrawTriangle", false);
            }
            else
            {
                bDebugDraw = true;
                GetResourceManager()->GetResource<COpenGLShader>("DefaultShader")->SetBool("bDrawTriangle", true);
            }
        }
        if (CInput::KeyHold(S3D_KEY_F5, 0.02f))
        {
            //GetInterop()->Reload();
        }
        if (CInput::KeyHold(S3D_KEY_LEFT_ALT, 0.1f))
        {
            if (bCursorMode)
            {
                bCursorMode = false;
                GetWindow()->SetCursorMode(ECursorMode::Hidden);
                GetScene()->GetActiveCamera()->bCanMovePitch = true;
                GetScene()->GetActiveCamera()->bCanMoveYaw = true;
            }
            else
            {
                bCursorMode = true;
                GetWindow()->SetCursorMode(ECursorMode::Visible);
                GetScene()->GetActiveCamera()->bCanMovePitch = false;
                GetScene()->GetActiveCamera()->bCanMoveYaw = false;
            }
        }
    }

    virtual void OnStop() override
    {
        
    }

private:
    CActor* Player;
};

#pragma once

int main()
{
    CApplication* Application = new CApplication(new CEditorEngine());
    
    Application->Start();

    Application->Run();

    Application->Stop();

    delete Application;

    return 0;
}