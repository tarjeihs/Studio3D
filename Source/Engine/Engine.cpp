#include "EnginePCH.h"
#include "Engine.h"

#include "GLFW/glfw3.h"
#include "Core/Camera.h"
#include "Core/Scene.h"
#include "Core/Window.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Renderer/Actor.h"
#include "Renderer/Shader.h"

#include <iostream>

std::vector<glm::vec3> vertices = {
    // Front face
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    // Back face
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    // Left face
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    // Right face
    glm::vec3( 0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    // Top face
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    // Bottom face
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f, -0.5f),
};

std::vector<glm::vec3> normals = {
    // Front face
    glm::vec3( 0.0f,  0.0f,  1.0f),
    glm::vec3( 0.0f,  0.0f,  1.0f),
    glm::vec3( 0.0f,  0.0f,  1.0f),
    glm::vec3( 0.0f,  0.0f,  1.0f),
    // Back face
    glm::vec3( 0.0f,  0.0f, -1.0f),
    glm::vec3( 0.0f,  0.0f, -1.0f),
    glm::vec3( 0.0f,  0.0f, -1.0f),
    glm::vec3( 0.0f,  0.0f, -1.0f),
    // Left face
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    // Right face
    glm::vec3( 1.0f,  0.0f,  0.0f),
    glm::vec3( 1.0f,  0.0f,  0.0f),
    glm::vec3( 1.0f,  0.0f,  0.0f),
    glm::vec3( 1.0f,  0.0f,  0.0f),
    // Top face
    glm::vec3( 0.0f,  1.0f,  0.0f),
    glm::vec3( 0.0f,  1.0f,  0.0f),
    glm::vec3( 0.0f,  1.0f,  0.0f),
    glm::vec3( 0.0f,  1.0f,  0.0f),
    // Bottom face
    glm::vec3( 0.0f, -1.0f,  0.0f),
    glm::vec3( 0.0f, -1.0f,  0.0f),
    glm::vec3( 0.0f, -1.0f,  0.0f),
    glm::vec3( 0.0f, -1.0f,  0.0f),
};

std::vector<glm::vec2> uvs = {
    // Front face
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    // Back face
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    // Left face
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    // Right face
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    // Top face
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    // Bottom face
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
};

std::vector<uint32> indices = {
    // Front face
    0, 1, 2, 0, 2, 3,
    // Back face
    4, 5, 6, 4, 6, 7,
    // Left face
    8, 9, 10, 8, 10, 11,
    // Right face
    12, 13, 14, 12, 14, 15,
    // Top face
    16, 17, 18, 16, 18, 19,
    // Bottom face
    20, 21, 22, 20, 22, 23
};

void CEngine::Start()
{
    GWindow = new CWindowsWindow(SWindowSpecification { "Engine", 1200, 900 } );
    
    GWindow->CreateNativeWindow();

    CCamera::GCamera = new CCamera(glm::vec3(0.0f, 0.0f, 3.0f));

    Scene = new CScene();
}

void CEngine::Run()
{
    COpenGLShader* DefaultShader = new COpenGLShader();
    DefaultShader->LoadSourceFile(EShaderType::Vertex, "Shaders/DefaultVS.glsl"); 
    DefaultShader->LoadSourceFile(EShaderType::Fragment, "Shaders/DefaultFS.glsl");
    DefaultShader->Compile();

    CMaterial* Material = new CMaterial();
    Material->SetShader(DefaultShader);
    
    CMesh* Mesh = new CMesh();
    Mesh->SetMaterial(Material);
    Mesh->UploadAssetData(vertices, normals, uvs, indices);

    CActor* Actor = new CActor();
    Actor->SetMesh(Mesh);
    Actor->SetActorLocation({0.0f, 0.0f, 0.0f});

    CActor* Actor2 = new CActor();
    Actor2->SetMesh(Mesh);
    Actor2->SetActorLocation({3.0f, 0.0f, 0.0f});

    CActor* Actor3 = new CActor();
    Actor3->SetMesh(Mesh);
    Actor3->SetActorLocation({-3.0f, 0.0f, 0.0f});

    Scene->Actors.Push(Actor);
    Scene->Actors.Push(Actor2);
    Scene->Actors.Push(Actor3);
    
    constexpr float CameraSpeed = 5.f;
    while (!GWindow->ShouldClose())
    {
        Time.Update();

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        GWindow->Poll();

        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_W) == GLFW_PRESS) CCamera::GCamera->Position += CameraSpeed * CCamera::GCamera->Front * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_S) == GLFW_PRESS) CCamera::GCamera->Position -= CameraSpeed * CCamera::GCamera->Front * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS) CCamera::GCamera->Position -= glm::normalize(glm::cross(CCamera::GCamera->Front, CCamera::GCamera->Up)) * CameraSpeed * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS) CCamera::GCamera->Position += glm::normalize(glm::cross(CCamera::GCamera->Front, CCamera::GCamera->Up)) * CameraSpeed * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) CCamera::GCamera->Position += CCamera::GCamera->WorldUp * CameraSpeed * Time.GetDeltaTime();
        if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) CCamera::GCamera->Position -= CCamera::GCamera->WorldUp * CameraSpeed * Time.GetDeltaTime();
        
        CCamera::GCamera->CalculateCameraTransform();

        for (CActor* Actor : Scene->Actors)
        {
            Actor->Tick();
        }

        GWindow->Swap();
    }

    DefaultShader->Delete();
}

void CEngine::Stop()
{
    delete CCamera::GCamera;
    
    GWindow->DestroyWindow();

    delete GWindow;
}