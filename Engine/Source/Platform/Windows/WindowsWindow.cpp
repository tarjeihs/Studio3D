#include "EnginePCH.h"
#include "WindowsWindow.h"

#include <iostream>
#include <glfw/glfw3.h>
#include <glad/glad.h>

#include "Core/Engine.h"
#include "Core/Camera.h"
#include "Core/Input.h"
#include "Core/KeyCode.h"
#include "Core/Scene.h"
#include "Math/Math.h"

// Mouse Controllers
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
    glfwSwapInterval(1); // Enable vsync
    
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

        CCameraComponent* Camera = GetScene()->GetActiveCamera();

        if (Camera->bCanMovePitch)
        {
            Camera->Pitch = pitch;
        }

        if (Camera->bCanMoveYaw)
        {
            Camera->Yaw = yaw;
        }
    });

    glfwSetKeyCallback(Window, [](GLFWwindow* Window, int32 KeyCode, int32 ScanCode, int32 Action, int32 Mod)
    {
        SWindowUserData& UserData = *(SWindowUserData*)glfwGetWindowUserPointer(Window);

        auto Now = std::chrono::steady_clock::now();
        
        if (KeyCode == S3D_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(Window, true);
        }

        if (Action == GLFW_PRESS)
        {
            CInput::GetKeyPressData(KeyCode).bIsPressed = true;
            CInput::GetKeyPressData(KeyCode).Start = Now;
        }
        else if (Action == GLFW_RELEASE)
        {
            CInput::GetKeyPressData(KeyCode).bIsPressed = false;
        }
    });

    glfwSetFramebufferSizeCallback(Window, [](GLFWwindow* Window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ASSERT(false, "Failed to initialize GLAD");
        glfwTerminate();
        return;
    }

    int windowWidth, windowHeight;
    glfwGetWindowSize(Window, &windowWidth, &windowHeight);

    GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* VideoMode = glfwGetVideoMode(PrimaryMonitor);

    int windowPosX = (VideoMode->width - windowWidth) / 2;
    int windowPosY = (VideoMode->height - windowHeight) / 2;
    glfwSetWindowPos(Window, windowPosX, windowPosY);
    
    glViewport(0, 0, Specification.Width, Specification.Height);
    
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    WindowHandle = Window;

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;
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

void CWindowsWindow::SetCursorMode(ECursorMode CursorMode)
{
    switch (CursorMode)
    {
        case ECursorMode::Hidden: { MoveCursorToCenter(); glfwSetInputMode((GLFWwindow*)WindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED); break; }
        case ECursorMode::Visible: { MoveCursorToCenter(); glfwSetInputMode((GLFWwindow*)WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL); break; }
        default: { break; }
    }
}

void CWindowsWindow::MoveCursorToCenter()
{
    int32 Width, Height;
    glfwGetWindowSize((GLFWwindow*)WindowHandle, &Width, &Height);

    double CenterX = Width / 2.0;
    double CenterY = Height / 2.0;

    glfwSetCursorPos((GLFWwindow*)WindowHandle, CenterX, CenterY);
}
