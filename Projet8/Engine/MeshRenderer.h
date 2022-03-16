#pragma once

#include "Component.h"

class MeshRenderer : public Component
{

public:
    const char* GetType() override { return NAMEOF(MeshRenderer); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }

    MeshRenderer(LPCWSTR path);
    ~MeshRenderer() override;

    void Start() override;
    void Update(float runTime, float deltaTime) override;

private:
    ID3DXMesh* _pmesh;
    LPCWSTR _path;

};
