#pragma once
#include "fwd.hpp"
#include "vec3.hpp"
#include "Engine/Platform/OpenGL/OpenGLShader.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

constexpr float YAW         = -90.0f;
constexpr float PITCH       =  0.0f;
constexpr float SPEED       =  2.5f;
constexpr float SENSITIVITY =  0.1f;
constexpr float Zoom        =  66.0f;

class CCamera
{
public:
    CCamera(glm::vec3 InPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 InUp = glm::vec3(0.0f, 1.0f, 0.0f), float InYaw = YAW, float InPitch = PITCH)
            : Position(InPosition), WorldUp(InUp), Yaw(InYaw), Pitch(InPitch), FieldOfView(Zoom)
    {
        CalculateCameraTransform();
    }
    
    void CalculateCameraTransform();

    // Transforms world space coordinates to camera space coordinates.
    inline glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up); 
    }

    // Transforms camera space coordinates to screen space coordinates.
    inline glm::mat4 GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(FieldOfView), 800.0f / 600.0f, 0.1f, 100.0f);
    }
    
    glm::vec3 Position;
    glm::vec3 Front { 0.0f, 0.0f, -1.0f };
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    
    float Yaw;
    float Pitch;
    float FieldOfView;

    float CameraMovementSpeed;
    float CameraRotationSpeed;
};
