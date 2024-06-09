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

    Window = new CWindowsWindow(SWindowSpecification { "Engine", G_VIEWPORT_WIDTH, G_VIEWPORT_HEIGHT } );
    Window->CreateNativeWindow();
    Renderer = new COpenGLRenderer();
    Scene = new CScene();
    UI = new COpenGLImGui();
    UI->Enable();
    
    Application = CreateApplication();
    Application->OnStart();
}

void CEngine::Run()
{
    while (!Window->ShouldClose())
    {
        Time.Update();

        Window->Poll();
        
        Application->OnUpdate(Time.GetDeltaTime());

        Scene->Tick(Time.GetDeltaTime());

        Renderer->BeginFrame();
        for (CActor* Actor : Scene->GetActors())
        {
            Actor->Tick(Time.GetDeltaTime());
        }
        Renderer->EndFrame();

        UI->BeginFrame();
        UI->OnRender(Time.GetDeltaTime());
        UI->EndFrame();
        
        Window->Swap();
    }
}

void CEngine::Stop()
{
    UI->Disable();
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
    return UI;
}
