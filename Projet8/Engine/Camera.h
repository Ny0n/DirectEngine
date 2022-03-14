#pragma once

#include "Component.h"

class Camera : public Component
{

public:
    void Start() override;
    void Update(float runTime, float deltaTime) override;
 
};

