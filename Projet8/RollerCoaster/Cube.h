#pragma once

#include "EngineLib.h"

class Cube : public Component
{

public :
    const char* GetType() override { return NAMEOF(Cube); }
    ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

    void Start() override;
    void Update(float runTime, float deltaTime) override;

private:
    void CubeRender();
    void CubePlacement();

};
