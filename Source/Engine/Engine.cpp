#include "EnginePCH.h"
#include "Engine.h"

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
    while (!GWindow->ShouldClose())
    {
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GWindow->SwapAndPoll();
    }
}

void CEngine::Stop()
{
    GWindow->DestroyWindow();

    delete GWindow;
}
