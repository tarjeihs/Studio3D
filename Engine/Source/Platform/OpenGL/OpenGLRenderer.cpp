#include "EnginePCH.h"
#include "OpenGLRenderer.h"

#include "Core/Camera.h"
#include "Renderer/Material.h"
#include "Renderer/Mesh.h"
#include "Math/Transform.h"

void COpenGLRenderer::BeginFrame()
{
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void COpenGLRenderer::Submit(CMesh* Mesh, CMaterial* Material, CCamera* Camera, const STransform& Transform)
{
    CRenderCommand RenderCommand([Mesh, Material, Camera, Transform]()
    {
        glm::mat4 View = Camera->GetViewMatrix();
        glm::mat4 Projection = Camera->GetProjectionMatrix();
        glm::mat4 Model = Camera->GetViewModel(Transform);

        // Update model, view and projection matrices
        Material->SetParameter("view", View);
        Material->SetParameter("projection", Projection);
        Material->SetParameter("model", Model);
        Material->SetParameter("Camera.Position", Transform.Location);

        Material->Bind();
        Mesh->Draw();
    });
    RenderQueue.AddCommand(RenderCommand);
}

void COpenGLRenderer::EndFrame()
{
    RenderQueue.Sort();
    RenderQueue.ExecuteCommands();
}