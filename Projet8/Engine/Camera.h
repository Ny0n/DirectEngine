#pragma once

#include "Component.h"

class Camera : public Component
{

public:
    ComponentType GetType() override { return ComponentType::camera; }

    void Update(float runTime, float deltaTime) override;

};
