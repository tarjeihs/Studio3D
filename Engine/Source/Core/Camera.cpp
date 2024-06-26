﻿#include "EnginePCH.h"
#include "Camera.h"

#include <imgui.h>

#include "Engine.h"

#include <glm/glm.hpp>

void CCameraComponent::CalculateCameraTransform()
{
    glm::vec3 NewFront;
    NewFront.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    NewFront.y = glm::sin(glm::radians(Pitch));
    NewFront.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));

    Front = glm::normalize(NewFront);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

    ViewMatrix = glm::lookAt(GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + Front, Up);
    ProjectionMatrix = glm::perspective(glm::radians(FieldOfView), static_cast<float>(PARAMETER_VIEWPORT_WIDTH) / static_cast<float>(PARAMETER_VIEWPORT_HEIGHT), ZNear, ZFar);
}

void CCameraComponent::OnImGuiRender()
{
    ImGui::Text("CameraComponent");
    ImGui::DragFloat("Field Of View", &FieldOfView);
    ImGui::DragFloat("Z Near", &ZNear);
    ImGui::DragFloat("Z Far", &ZFar);
}

void CCameraComponent::SetFieldOfView(float NewFOV)
{
    FieldOfView = NewFOV;
}
