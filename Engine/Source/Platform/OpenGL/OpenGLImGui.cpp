#include "EnginePCH.h"
#include "OpenGLImGui.h"

#include <imgui_impl_opengl3.h>

#include "Core/Scene.h"

void COpenGLImGui::Enable()
{
    ImGui::CreateContext();
    ImGuiIO& IO = ImGui::GetIO();
    //IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

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
    {
        ImGui::Begin("Scene Hierarchy", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
         
        static int ActorIndex = -1;
        for (int Index = 0; Index < GetScene()->GetActors().GetSize(); ++Index)
        {
            std::string ID = std::to_string(GetScene()->GetActors()[Index]->GetUUID()).c_str();
            std::string Name = GetScene()->GetActors()[Index]->Name.c_str();

            if (ImGui::Selectable((Name + "##" + ID).c_str(), ActorIndex == Index))
            {
                ActorIndex == Index ? ActorIndex = -1 : ActorIndex = Index;
            }
        }
        ImGui::End();

        ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        if (ActorIndex != -1) 
        {            
            CActor* Actor = GetScene()->GetActors()[ActorIndex];
            
            ImGui::Separator();
            ImGui::Text("Actor UUID: %d", Actor->GetUUID());
            ImGui::ColorButton(("##red" + std::to_string(ActorIndex)).c_str(), ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Location_X", &Actor->Transform.Location.x, 0.01f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            ImGui::SameLine();
            ImGui::ColorButton(("##green" + std::to_string(ActorIndex)).c_str(), ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Location_Y", &Actor->Transform.Location.y, 0.01f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            ImGui::SameLine();
            ImGui::ColorButton(("##blue" + std::to_string(ActorIndex)).c_str(), ImVec4(0.0f, 0.0f, 1.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Location_Z", &Actor->Transform.Location.z, 0.01f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    
            ImGui::Separator();
            ImGui::ColorButton(("##red" + std::to_string(ActorIndex)).c_str(), ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Rotation_X", &Actor->Transform.Rotation.x, 0.1f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            ImGui::SameLine();
            ImGui::ColorButton(("##green" + std::to_string(ActorIndex)).c_str(), ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Rotation_Y", &Actor->Transform.Rotation.y, 0.1f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            ImGui::SameLine();
            ImGui::ColorButton(("##blue" + std::to_string(ActorIndex)).c_str(), ImVec4(0.0f, 0.0f, 1.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Rotation_Z", &Actor->Transform.Rotation.z, 0.1f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    
            ImGui::Separator();
            ImGui::ColorButton(("##red" + std::to_string(ActorIndex)).c_str(), ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Scale_X", &Actor->Transform.Scale.x, 0.01f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            ImGui::SameLine();
            ImGui::ColorButton(("##green" + std::to_string(ActorIndex)).c_str(), ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Scale_Y", &Actor->Transform.Scale.y, 0.01f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            ImGui::SameLine();
            ImGui::ColorButton(("##blue" + std::to_string(ActorIndex)).c_str(), ImVec4(0.0f, 0.0f, 1.0f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(5, 20));
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(75.0f);
            ImGui::DragFloat("##Scale_Z", &Actor->Transform.Scale.z, 0.01f, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

            ImGui::Separator();
            ImGui::Text("Components: %d", Actor->GetComponents().GetSize());

            static int ComponentIndex = -1;
            for (int Index = 0; Index < Actor->GetComponents().GetSize(); ++Index)
            {
                if (ImGui::Selectable(Actor->GetComponents()[Index]->GetName().c_str(), ComponentIndex == Index))
                {
                    ComponentIndex == Index ? ComponentIndex = -1 : ComponentIndex = Index;
                    CComponent* Comp = new CComponent();
                }
            }

        }
        ImGui::Unindent();
        
        ImGui::End();
    }

    {
        ImGui::Begin("Statistics", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::Text("FPS: %f", 1.0f / GetEngine()->Time.GetDeltaTime());
        ImGui::Text("MS: %f", GetEngine()->Time.GetDeltaTime());
        ImGui::Text("Draw Calls: %d", GetEngine()->Metrics.DrawCallCounter);
        ImGui::Text("Current Object Allocated: %d", GetEngine()->Metrics.CurrentObjectAllocated);
        ImGui::Text("Total Objects Allocated: %d", GetEngine()->Metrics.TotalObjectAllocated);
        ImGui::Text("Current Size: %d (KB)", GetEngine()->Metrics.CurrentSizeAllocated / 10);
        ImGui::Text("Total Size: %d (KB)", GetEngine()->Metrics.TotalSizeAllocated / 10);
        ImGui::End();
    }
}
