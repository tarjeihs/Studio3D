    #include <iostream>

#include "EngineModule.h"
#include "Core/Entrypoint.h"
#include "Core/KeyCode.h"


class CSandboxApplication : public CApplication
{
public:
    CSandboxApplication(const std::string& InName, uint32 InWidth, uint32 InHeight)
        : CApplication(InName, InWidth, InHeight)
    {
    }
    
    virtual void OnStart() override
    {
        GetResourceManager()->LoadShaderAsset("DefaultShader", "D:/Laboratory/Modules/Studio3D/Engine/Source/Shaders/DefaultVS.glsl", "D:/Laboratory/Modules/Studio3D/Engine/Source/Shaders/DefaultFS.glsl");
        GetResourceManager()->LoadMeshAsset("123", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/D-21-11.fbx");
        
        CActor* MeshActor = GetScene()->SpawnActor("MeshActor"); 
        MeshActor->SetActorLocation(glm::vec3(0));

        CMeshComponent* MeshComponent = MeshActor->AddComponent<CMeshComponent>(R"(MeshComp)");
        MeshComponent->SetMesh(GetResourceManager()->GetResource<CMesh>("Model"));
    
        CActor* PointLightActor = GetScene()->SpawnActor("PointLightActor");
        PointLightActor->SetActorLocation({5.0f, -1.0f, 0.0f});
        PointLightActor->AddComponent<CPointLightComponent>(R"(PointLightComp)");

        CActor* PointLightActor2 = GetScene()->SpawnActor("PointLightActor2");
        PointLightActor2->SetActorLocation({0.0f, 3.0f, 0.0f});
        PointLightActor2->AddComponent<CPointLightComponent>(R"(PointLightComp)");

        CActor* Sphere = GetScene()->SpawnActor("Sphere");
        Sphere->SetActorLocation({3.0f, 0.0f, 0.0f});
        Sphere->AddComponent<CPrimitiveComponent>(R"(SphereMeshComp)", EMeshType::Sphere);

        CActor* Cube = GetScene()->SpawnActor("Cube");
        Cube->SetActorLocation({-3.0f, 0.0f, 0.0f});
        Cube->AddComponent<CPrimitiveComponent>(R"(CubeMeshComp)", EMeshType::Cube);

        CActor* Capsule = GetScene()->SpawnActor("Capsule");
        Capsule->SetActorLocation({-3.0f, 0.0f, 3.0f});
        Capsule->AddComponent<CPrimitiveComponent>(R"(CapsuleMeshComp)", EMeshType::Capsule);

        Player = GetScene()->SpawnActor("Player");
        Player->SetActorLocation(glm::vec3(0.0f, 0.0f, 2.5f));
        CCameraComponent* Camera = Player->AddComponent<CCameraComponent>(R"(CameraComponent)");
        GetScene()->SetActiveCamera(Camera);

        CActor* Capsule2 = GetScene()->SpawnActor("Capsule");
        Capsule2->SetActorLocation({-3.0f, 0.0f, 3.0f});
        Capsule2->AddComponent<CPrimitiveComponent>(R"(CapsuleMeshComp)", EMeshType::Capsule);
    }

    float CameraSpeed = 1.5f;
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

CApplication* CreateApplication()
{
    return new CSandboxApplication("Sandbox", 1400, 900);
}
