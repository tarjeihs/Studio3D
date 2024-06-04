#include "EnginePCH.h"
#include "OpenGLWindow.h"

#include <iostream>
#include <glfw/glfw3.h>

#include "Engine/Engine.h"
#include "glad/glad.h"

void COpenGLWindow::CreateWindow()
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
    
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1); // Enable vsync
    
    glfwSetKeyCallback(Window, [](GLFWwindow* Window, int32 KeyCode, int32 ScanCode, int32 Action, int32 Mod)
    {
        SWindowUserData& UserData = *(SWindowUserData*)glfwGetWindowUserPointer(Window);
        //switch (Action)
        //{
        //    case GLFW_PRESS: { CKeyPressedEvent Event(KeyCode, 0); UserData.EventCallback(Event); break; }
        //    case GLFW_REPEAT: { CKeyPressedEvent Event(KeyCode, 1); UserData.EventCallback(Event); break; }
        //    case GLFW_RELEASE: { CKeyReleasedEvent Event(KeyCode); UserData.EventCallback(Event); break; }
        //}
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ASSERT(false, "Failed to initialize GLAD");
        glfwTerminate();
        return;
    }

    glEnable(GL_DEPTH_TEST);
    
    WindowHandle = Window;
}

void COpenGLWindow::DestroyWindow()
{
    glfwDestroyWindow((GLFWwindow*)WindowHandle);
    glfwTerminate();
}

void COpenGLWindow::Poll()
{
    glfwPollEvents();
}

void COpenGLWindow::Swap()
{
    glfwSwapBuffers((GLFWwindow*)WindowHandle);
}

bool COpenGLWindow::ShouldClose() const
{
    return glfwWindowShouldClose((GLFWwindow*)WindowHandle);
}
