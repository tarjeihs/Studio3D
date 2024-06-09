#include "EnginePCH.h"
#include "Engine.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <sstream>

#include "Camera.h"
#include "Scene.h"
#include "Window.h"
#include "Actor.h"
#include "AssetManager.h"
#include "Renderer/Mesh.h"
#include "Components/MeshComponent.h"
#include "Components/PrimitiveMeshComponent.h"
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Components/PointLightComponent.h"

CWindow* GWindow = nullptr;
CEngine* CEngine::GEngine = nullptr;

void CEngine::Start()
{
    GEngine = this;

    GWindow = new CWindowsWindow(SWindowSpecification { "Engine", G_VIEWPORT_WIDTH, G_VIEWPORT_HEIGHT } );
    GWindow->CreateNativeWindow();

    Renderer = new COpenGLRenderer();
    Scene = new CScene();

    CCamera::GCamera = new CCamera(glm::vec3(0.0f, 0.0f, 2.0f));

    GetResourceManager()->LoadShaderAsset("DefaultShader", "D:/Laboratory/Modules/Studio3D/Engine/Source/Shaders/DefaultVS.glsl", "D:/Laboratory/Modules/Studio3D/Engine/Source/Shaders/DefaultFS.glsl");
    GetResourceManager()->LoadMeshAsset("123", "D:/Laboratory/Modules/Studio3D/Engine/Content/UtahTeapot/D-21-11.fbx");
    //GetResourceManager()->LoadTextureAsset("TextureDiffuse", "D:/Laboratory/Modules/Engine/Content/UtahTeapot/textures/d-21-11-v0-diffuse-alt.png");
    //GetResourceManager()->LoadTextureAsset("TextureNormal", "D:/Laboratory/Modules/Engine/Content/UtahTeapot/textures/d-21-11-v0-normal.png");
}

void CEngine::Run()
{
    CActor* MeshActor = Scene->SpawnActor(); 
    MeshActor->SetActorLocation(glm::vec3(0));

    CMeshComponent* MeshComponent = MeshActor->AddComponent<CMeshComponent>();
    MeshComponent->SetMesh(GetResourceManager()->GetResource<CMesh>("Model"));
    
    CActor* PointLightActor = Scene->SpawnActor();
    PointLightActor->SetActorLocation({5.0f, -1.0f, 0.0f});
    PointLightActor->AddComponent<CPointLightComponent>();

    CActor* PointLightActor2 = Scene->SpawnActor();
    PointLightActor2->SetActorLocation({0.0f, 3.0f, 0.0f});
    PointLightActor2->AddComponent<CPointLightComponent>();

    CActor* Sphere = Scene->SpawnActor();
    Sphere->SetActorLocation({3.0f, 0.0f, 0.0f});
    Sphere->AddComponent<CPrimitiveComponent>(EMeshType::Sphere);

    CActor* Cube = Scene->SpawnActor();
    Cube->SetActorLocation({-3.0f, 0.0f, 0.0f});
    Cube->AddComponent<CPrimitiveComponent>(EMeshType::Cube);

    CActor* Capsule = Scene->SpawnActor();
    Capsule->SetActorLocation({-3.0f, 0.0f, 3.0f});
    Capsule->AddComponent<CPrimitiveComponent>(EMeshType::Capsule);
    static bool bDebugDraw = false;
    
    constexpr float CameraSpeed = 1.5f;
    while (!GWindow->ShouldClose())
    {
        Time.Update();

        GWindow->Poll();

        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_W) == GLFW_PRESS) CCamera::GCamera->Position += CameraSpeed * CCamera::GCamera->Front * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_S) == GLFW_PRESS) CCamera::GCamera->Position -= CameraSpeed * CCamera::GCamera->Front * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS) CCamera::GCamera->Position -= glm::normalize(glm::cross(CCamera::GCamera->Front, CCamera::GCamera->Up)) * CameraSpeed * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS) CCamera::GCamera->Position += glm::normalize(glm::cross(CCamera::GCamera->Front, CCamera::GCamera->Up)) * CameraSpeed * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) CCamera::GCamera->Position += CCamera::GCamera->WorldUp * CameraSpeed * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) CCamera::GCamera->Position -= CCamera::GCamera->WorldUp * CameraSpeed * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_F1) == GLFW_PRESS)
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

        Renderer->BeginFrame();

        for (CActor* Actor : Scene->GetActors())
        {
            Actor->Tick(Time.GetDeltaTime());
        }

        Renderer->EndFrame();
        
        CCamera::GCamera->CalculateCameraTransform();

        GWindow->Swap();
    }

   // DefaultShader->Delete();
}

void CEngine::Stop()
{
    delete CCamera::GCamera;
    
    GWindow->DestroyWindow();

    delete GWindow;
}

CScene* CEngine::GetScene() const
{
    return Scene;
}

CRenderer* CEngine::GetRenderer() const
{
    return Renderer;
}
