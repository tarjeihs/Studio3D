#pragma once
#include <iostream>

#include "fwd.hpp"
#include "vec3.hpp"
#include "Engine/Platform/OpenGL/OpenGLShader.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class CActor;
constexpr float YAW         = -90.0f;
constexpr float PITCH       =  0.0f;
constexpr float SPEED       =  2.5f;
constexpr float SENSITIVITY =  0.1f;
constexpr float Zoom        =  66.0f;

struct FTransform
{
    FTransform()
        : Location(0), Rotation(0), Scale(1)
    {
    }
    
    glm::vec3 Location;
    glm::vec3 Rotation;
    glm::vec3 Scale;
};

class CCamera
{
public:
    static CCamera* GCamera;
    
    CCamera(glm::vec3 InPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 InUp = glm::vec3(0.0f, 1.0f, 0.0f), float InYaw = YAW, float InPitch = PITCH)
            : Position(InPosition), WorldUp(InUp), Yaw(InYaw), Pitch(InPitch), FieldOfView(Zoom)
    {
        CalculateCameraTransform();
    }

    void CalculateCameraTransform();

    // Transforms world space coordinates to camera space coordinates.
    inline glm::mat4 GetViewMatrix() const
    {
        return ViewMatrix;
    }

    // Transforms camera space coordinates to screen space coordinates.
    inline glm::mat4 GetProjectionMatrix() const
    {
        return ProjectionMatrix;
    }

    // Transforms local space coordinates to world space coordinates.
    inline static glm::mat4 GetViewModel(const FTransform& LocalTransform)
    {
        glm::mat4 LocalToWorldSpace = glm::identity<glm::mat4>();
        LocalToWorldSpace = glm::translate(LocalToWorldSpace, LocalTransform.Location);
        LocalToWorldSpace = glm::rotate(LocalToWorldSpace, glm::radians(LocalTransform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        LocalToWorldSpace = glm::rotate(LocalToWorldSpace, glm::radians(LocalTransform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        LocalToWorldSpace = glm::rotate(LocalToWorldSpace, glm::radians(LocalTransform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        LocalToWorldSpace = glm::scale(LocalToWorldSpace, LocalTransform.Scale);
        return LocalToWorldSpace;
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

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
};
