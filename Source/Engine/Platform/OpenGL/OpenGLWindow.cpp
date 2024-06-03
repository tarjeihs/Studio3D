#include "EnginePCH.h"
#include "OpenGLWindow.h"

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
    
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ASSERT(false, "Failed to initialize GLAD");   
        return;
    }
    
    WindowHandle = Window;
}

void COpenGLWindow::DestroyWindow()
{
    glfwDestroyWindow((GLFWwindow*)WindowHandle);
    glfwTerminate();
}

void COpenGLWindow::SwapAndPoll()
{
    glfwSwapBuffers((GLFWwindow*)WindowHandle);
    glfwPollEvents();
}

bool COpenGLWindow::ShouldClose() const
{
    return glfwWindowShouldClose((GLFWwindow*)WindowHandle);
}
