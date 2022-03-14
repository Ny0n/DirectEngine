#pragma once

#include "EngineLib.h"

class Cube : public Component
{

public :
    ComponentType GetType() override { return ComponentType::mono_behaviour; }

    Cube(GameObject* g, float size);
    
    void Update(float runTime, float deltaTime) override;

private:
    Transform* _transform;
    float _size;

    void CubeRender();
    void CubePlacement();

};
