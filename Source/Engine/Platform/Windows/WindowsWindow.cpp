#include "EnginePCH.h"
#include "WindowsWindow.h"

#include <iostream>
#include <glfw/glfw3.h>

#include "Engine/Engine.h"
#include "Engine/Core/Camera.h"
#include "glad/glad.h"
#include "gtc/quaternion.hpp"

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  66.0f;

void CWindowsWindow::CreateNativeWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* Window = glfwCreateWindow(Specification.Width, Specification.Height, Specification.Title, nullptr, nullptr);
    if (Window == nullptr)
    {
        ASSERT(false, "Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    
    glfwSetWindowUserPointer(Window, &UserData);
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(0); // Enable vsync

    glfwSetCursorPosCallback(Window, [](GLFWwindow* Window, double X, double Y)
    {
        // TODO: Access Camera through the user data pointer.
        SWindowUserData& UserData = *(SWindowUserData*)glfwGetWindowUserPointer(Window);
        
        float xpos = static_cast<float>(X);
        float ypos = static_cast<float>(Y);
        
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;
        
        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        
        yaw += xoffset;
        pitch += yoffset;
        
        pitch = Math::Clamp(pitch, -89.9f, 89.9f);
        
        CCamera::GCamera->Pitch = pitch;
        CCamera::GCamera->Yaw = yaw;
        CCamera::GCamera->CalculateCameraTransform();
    });

    glfwSetKeyCallback(Window, [](GLFWwindow* Window, int32 KeyCode, int32 ScanCode, int32 Action, int32 Mod)
    {
        SWindowUserData& UserData = *(SWindowUserData*)glfwGetWindowUserPointer(Window);
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ASSERT(false, "Failed to initialize GLAD");
        glfwTerminate();
        return;
    }

    glViewport(0, 0, Specification.Width, Specification.Height);
    
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    WindowHandle = Window;
}

void CWindowsWindow::DestroyWindow()
{
    glfwDestroyWindow((GLFWwindow*)WindowHandle);
    glfwTerminate();
}

void CWindowsWindow::Poll()
{
    glfwPollEvents();
}

void CWindowsWindow::Swap()
{
    glfwSwapBuffers((GLFWwindow*)WindowHandle);
}

bool CWindowsWindow::ShouldClose() const
{
    return glfwWindowShouldClose((GLFWwindow*)WindowHandle);
}
