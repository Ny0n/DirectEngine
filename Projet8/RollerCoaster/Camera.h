#pragma once
#include "Component.h"
class Camera :
    public Component
{
    void Start();
    void Update(float runTime, float deltaTime);
 
};

