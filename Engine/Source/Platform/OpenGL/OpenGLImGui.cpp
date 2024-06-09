#include "EnginePCH.h"
#include "OpenGLImGui.h"

#include <imgui_impl_opengl3.h>

void COpenGLImGui::Enable()
{
    ImGui::CreateContext();
    ImGuiIO& IO = ImGui::GetIO();
    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(GetWindow()->GetNativeWindow()), true);
    ImGui_ImplOpenGL3_Init("#version 410");
    
    ImGui::StyleColorsDark();
}

void COpenGLImGui::Disable()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void COpenGLImGui::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void COpenGLImGui::EndFrame()
{
    ImGuiIO& IO = ImGui::GetIO();
    IO.DisplaySize = ImVec2((float)GetEngine()->GetWindow()->GetWidth(), (float)GetEngine()->GetWindow()->GetHeight());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void COpenGLImGui::OnRender(float DeltaTime)
{
    //static bool showDemoWindow = true;
    //ImGui::ShowDemoWindow(&showDemoWindow);

    // Your ImGui code here
    ImGui::Begin("Example");
    ImGui::Text("Hello, world!");
    ImGui::End();
}
