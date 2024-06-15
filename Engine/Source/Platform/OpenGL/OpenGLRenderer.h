#pragma once

#include "Renderer/Renderer.h"

class CMaterialInstance;

class COpenGLRenderer : public CRenderer
{
public:
    virtual void BeginFrame() override;
    virtual void Submit(CMesh* Mesh, CMaterial* Material, CMaterialInstance* MaterialInstance, const STransform& Transform) override;
    //virtual void Submit(CMesh* Mesh, CMaterialInstance* MaterialInstance, CCamera* Camera) override;
    virtual void EndFrame() override;
};
