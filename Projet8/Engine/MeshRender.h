#pragma once
#include "Component.h"
class MeshRender :
    public Component
{
public:
    const char* GetType() override { return NAMEOF(MeshRender); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }

    MeshRender(string fileName);
    ~MeshRender();
    void Update(float runTime, float deltaTime) override;

private:
    ID3DXMesh* _pmesh;

    void Render();
    void Placement();

};
//   
//};

