#include <iostream>

#include "EngineModule.h"
#include "Core/Entrypoint.h"
#include "Core/KeyCode.h"


class CSandboxApplication : public CApplication
{
public:
    virtual void OnStart() override
    {
        GetResourceManager()->LoadShaderAsset("DefaultShader", "D:/Laboratory/Modules/Studio3D/Engine/Source/Shaders/DefaultVS.glsl", "D:/Laboratory/Modules/Studio3D/Engine/Source/Shaders/DefaultFS.glsl");
        GetResourceManager()->LoadMeshAsset("123", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/D-21-11.fbx");
        
        CActor* MeshActor = GetScene()->SpawnActor(); 
        MeshActor->SetActorLocation(glm::vec3(0));

        CMeshComponent* MeshComponent = MeshActor->AddComponent<CMeshComponent>();
        MeshComponent->SetMesh(GetResourceManager()->GetResource<CMesh>("Model"));
    
        CActor* PointLightActor = GetScene()->SpawnActor();
        PointLightActor->SetActorLocation({5.0f, -1.0f, 0.0f});
        PointLightActor->AddComponent<CPointLightComponent>();

        CActor* PointLightActor2 = GetScene()->SpawnActor();
        PointLightActor2->SetActorLocation({0.0f, 3.0f, 0.0f});
        PointLightActor2->AddComponent<CPointLightComponent>();

        CActor* Sphere = GetScene()->SpawnActor();
        Sphere->SetActorLocation({3.0f, 0.0f, 0.0f});
        Sphere->AddComponent<CPrimitiveComponent>(EMeshType::Sphere);

        CActor* Cube = GetScene()->SpawnActor();
        Cube->SetActorLocation({-3.0f, 0.0f, 0.0f});
        Cube->AddComponent<CPrimitiveComponent>(EMeshType::Cube);

        CActor* Capsule = GetScene()->SpawnActor();
        Capsule->SetActorLocation({-3.0f, 0.0f, 3.0f});
        Capsule->AddComponent<CPrimitiveComponent>(EMeshType::Capsule);

        Player = GetScene()->SpawnActor();
        Player->SetActorLocation(glm::vec3(0.0f, 0.0f, 2.5f));
        CCameraComponent* Camera = Player->AddComponent<CCameraComponent>();
        GetScene()->SetActiveCamera(Camera);
    }

    float CameraSpeed = 1.5f;
    bool bDebugDraw = false;

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
        if (CInput::KeyPress(S3D_KEY_LEFT_CONTROL))
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
    }

    virtual void OnStop() override
    {
        
    }

private:
    CActor* Player;
};

CApplication* CreateApplication()
{
    return new CSandboxApplication();
}
