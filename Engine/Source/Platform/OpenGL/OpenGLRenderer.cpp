#include "EnginePCH.h"
#include "OpenGLRenderer.h"

#include <iostream>

#include "Core/Camera.h"
#include "Core/Scene.h"
#include "Renderer/Material.h"
#include "Renderer/Mesh.h"
#include "Math/Transform.h"

void COpenGLRenderer::BeginFrame()
{
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void COpenGLRenderer::Submit(CMesh* Mesh, CMaterial* Material, CMaterialInstance* MaterialInstance, const STransform& Transform)
{
    CRenderCommand RenderCommand([Mesh, Material, MaterialInstance, Transform]()
    {
        glm::mat4 View = GetScene()->GetActiveCamera()->GetViewMatrix();
        glm::mat4 Projection = GetScene()->GetActiveCamera()->GetProjectionMatrix();
        glm::mat4 Model = GetScene()->GetActiveCamera()->GetViewModel(Transform);

        // Update model, view and projection matrices
        MaterialInstance->SetParameter("projection", Projection);
        MaterialInstance->SetParameter("model", Model);
        MaterialInstance->SetParameter("view", View);
        MaterialInstance->SetParameter("viewPos", Transform.Location);

        MaterialInstance->Bind();
        Mesh->Draw();
    });
    RenderQueue.AddCommand(RenderCommand);
}

void COpenGLRenderer::EndFrame()
{
    RenderQueue.Sort();
    RenderQueue.ExecuteCommands();
}