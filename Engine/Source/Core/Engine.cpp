#include "EnginePCH.h"
#include "Engine.h"

#include <iostream>
#include <sstream>

#include "Camera.h"
#include "Scene.h"
#include "Window.h"
#include "Actor.h"
#include "Renderer/Mesh.h"
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/OpenGL/OpenGLImGui.h"

CEngine* CEngine::GEngine = nullptr;

void CEngine::Start()
{
    GEngine = this;

    Window = new CWindowsWindow(SWindowSpecification { "Engine", PARAMETER_VIEWPORT_WIDTH, PARAMETER_VIEWPORT_HEIGHT } );
    Window->CreateNativeWindow();
    Renderer = new COpenGLRenderer();
    Scene = new CScene();
    ImGui = new COpenGLImGui();
    ImGui->Enable();
    
    Application = CreateApplication();
    Application->OnStart();
}

void CEngine::Run()
{
    while (!Window->ShouldClose())
    {
        Metrics.Reset();
        Time.Validate();

        Window->Poll();
        Application->OnUpdate(Time.GetDeltaTime());
        Scene->Tick(Time.GetDeltaTime());

        Renderer->BeginFrame();
        for (CActor* Actor : Scene->GetActors())
        {
            Actor->Tick(Time.GetDeltaTime());
        }
        Renderer->EndFrame();

        ImGui->BeginFrame();
        ImGui->OnRender(Time.GetDeltaTime());
        ImGui->EndFrame();
        
        Window->Swap();
    }
}

void CEngine::Stop()
{
    ImGui->Disable();
    Application->OnStop();
    Window->DestroyWindow();

    delete Window;
    delete Application;
}

CApplication* CEngine::GetApplication() const
{
    return Application;
}

CWindow* CEngine::GetWindow() const
{
return Window;
}

CScene* CEngine::GetScene() const
{
    return Scene;
}

CRenderer* CEngine::GetRenderer() const
{
    return Renderer;
}

CImGui* CEngine::GetImGui() const
{
    return ImGui;
}
