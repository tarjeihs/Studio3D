﻿#pragma once

#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Math/Transform.h"

class CActor;

// TODO: Subclass CActor
class CCamera
{
public:
    static CCamera* GCamera;
    
    CCamera(glm::vec3 InPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 InUp = glm::vec3(0.0f, 1.0f, 0.0f), float InYaw = -90.f, float InPitch = 0)
            : Position(InPosition), WorldUp(InUp), Yaw(InYaw), Pitch(InPitch), FieldOfView(66.0f)
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
    inline static glm::mat4 GetViewModel(const STransform& LocalTransform)
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

    float ZNear = 0.01f;
    float ZFar = 1000.0f;
    
    float CameraMovementSpeed;
    float CameraRotationSpeed;

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
};