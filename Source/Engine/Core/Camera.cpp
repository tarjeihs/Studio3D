#include "EnginePCH.h"
#include "Camera.h"

#include <glm.hpp>

void CCamera::CalculateCameraTransform()
{
    glm::vec3 NewFront;
    NewFront.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    NewFront.y = glm::sin(glm::radians(Pitch));
    NewFront.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));

    Front = glm::normalize(NewFront);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
