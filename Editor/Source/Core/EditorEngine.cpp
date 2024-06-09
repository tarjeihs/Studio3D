#include "EngineModule.h"
#include "Core/Entrypoint.h"

class CEditorEngine : public CEngine
{
public:
    CEditorEngine()
        : CEngine()
    {
    }

    ~CEditorEngine()
    {
    }

    virtual void OnUpdate(float DeltaTime) override
    {
        //if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_W) == GLFW_PRESS) CCamera::GCamera->Position += 1.0f * CCamera::GCamera->Front * Time.GetDeltaTime();
        //if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_S) == GLFW_PRESS) CCamera::GCamera->Position -= 1.0f * CCamera::GCamera->Front * Time.GetDeltaTime();
        //if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS) CCamera::GCamera->Position -= glm::normalize(glm::cross(CCamera::GCamera->Front, CCamera::GCamera->Up)) * CameraSpeed * Time.GetDeltaTime();
        //if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS) CCamera::GCamera->Position += glm::normalize(glm::cross(CCamera::GCamera->Front, CCamera::GCamera->Up)) * CameraSpeed * Time.GetDeltaTime();
        //if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) CCamera::GCamera->Position += CCamera::GCamera->WorldUp * 1.0f * Time.GetDeltaTime();
        //if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) CCamera::GCamera->Position -= CCamera::GCamera->WorldUp * 1.0f * Time.GetDeltaTime();
        //if (glfwGetKey((GLFWwindow*)GWindow->GetNativeWindow(), GLFW_KEY_F1) == GLFW_PRESS)
        //{
        //    if (bDebugDraw)
        //    {
        //        bDebugDraw = false;
        //        GetResourceManager()->GetResource<COpenGLShader>("DefaultShader")->SetBool("bDrawTriangle", false);
        //    }
        //    else
        //    {
        //        bDebugDraw = true;
        //        GetResourceManager()->GetResource<COpenGLShader>("DefaultShader")->SetBool("bDrawTriangle", true);
        //    }
        //}

    }

private:
};

CEngine* CreateEngine()
{
    return new CEditorEngine();
}
