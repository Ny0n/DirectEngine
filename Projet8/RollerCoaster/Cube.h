#pragma once

#include "EngineLib.h"

class Cube : public Component
{

public :
    const char* GetType() override { return NAMEOF(Cube); }
    ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

    Cube(GameObject* g, float size);
    
    void Update(float runTime, float deltaTime) override;

private:
    Transform* _transform;
    float _size;

    void CubeRender();
    void CubePlacement();

};
