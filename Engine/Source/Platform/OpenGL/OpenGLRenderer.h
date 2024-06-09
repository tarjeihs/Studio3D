#pragma once

#include "Renderer/Renderer.h"

class COpenGLRenderer : public CRenderer
{
public:
    virtual void BeginFrame() override;
    virtual void Submit(CMesh* Mesh, CMaterial* Material, CCamera* Camera, const STransform& Transform) override;
    virtual void EndFrame() override;
};
