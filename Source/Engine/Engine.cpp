#include "EnginePCH.h"
#include "Engine.h"

#include <iostream>

#include "Core/Camera.h"
#include "Core/Window.h"
 #include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLWindow.h"
#include "Renderer/Shader.h"

void CEngine::Start()
{
    GWindow = new COpenGLWindow(SWindowSpecification { "Engine", 800, 600 } );
    
    GWindow->CreateWindow();
}

void CEngine::Run()
{
    COpenGLShader* DefaultShader = new COpenGLShader();
    DefaultShader->LoadSourceFile(EShaderType::Vertex, "Shaders/VertexShader.glsl");
    DefaultShader->LoadSourceFile(EShaderType::Fragment, "Shaders/FragmentShader.glsl");
    DefaultShader->Compile();

    CCamera* Camera = new CCamera(glm::vec3(0.0f, 0.0f, 3.0f));

    constexpr float CameraSpeed = 0.01f;
    
    while (!GWindow->ShouldClose())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        GWindow->Poll();

        if (glfwGetKey((GLFWwindow*)GWindow->GetWindowHandle(), GLFW_KEY_W) == GLFW_PRESS)
            Camera->Position += CameraSpeed * Camera->Front;
        if (glfwGetKey((GLFWwindow*)GWindow->GetWindowHandle(), GLFW_KEY_S) == GLFW_PRESS)
            Camera->Position -= CameraSpeed * Camera->Front;
        if (glfwGetKey((GLFWwindow*)GWindow->GetWindowHandle(), GLFW_KEY_A) == GLFW_PRESS)
            Camera->Position -= glm::normalize(glm::cross(Camera->Front, Camera->Up)) * CameraSpeed;
        if (glfwGetKey((GLFWwindow*)GWindow->GetWindowHandle(), GLFW_KEY_D) == GLFW_PRESS)
            Camera->Position += glm::normalize(glm::cross(Camera->Front, Camera->Up)) * CameraSpeed;
        if (glfwGetKey((GLFWwindow*)GWindow->GetWindowHandle(), GLFW_KEY_SPACE) == GLFW_PRESS)
            Camera->Position += Camera->Up * CameraSpeed;
        if (glfwGetKey((GLFWwindow*)GWindow->GetWindowHandle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            Camera->Position -= Camera->Up * CameraSpeed;
        if (glfwGetKey((GLFWwindow*)GWindow->GetWindowHandle(), GLFW_KEY_E) == GLFW_PRESS)
            Camera->Yaw += 100.0f * CameraSpeed;
        if (glfwGetKey((GLFWwindow*)GWindow->GetWindowHandle(), GLFW_KEY_Q) == GLFW_PRESS)
            Camera->Yaw -= 100.0f * CameraSpeed;
        
        Camera->CalculateCameraTransform();

        DefaultShader->Use();
        glm::mat4 ViewMatrix = Camera->GetViewMatrix();
        glm::mat4 ViewProjection = Camera->GetProjectionMatrix();
        DefaultShader->SetMat4("view", ViewMatrix);
        DefaultShader->SetMat4("projection", ViewProjection);
        DefaultShader->Render();

        GWindow->Swap();
    }

    DefaultShader->Delete();
}

void CEngine::Stop()
{
    GWindow->DestroyWindow();

    delete GWindow;
}